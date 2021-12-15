from abc import ABCMeta, abstractmethod
import inspect
import types
from pycalcmodel.core.phy import ModelPhy
import os

"""
Phy interface file

This has been updated to handle 3 scenarios:
1) makePhy can be called inside of PHY_PHY1Example, and then if another PHY wishes to call PHY1Example the phy_name and phy_group_name will actually be set based on the highest level PHY in the call stack.
2) makePhy can be called inside of PHY_PHY1Example, and then if another PHY wishes to call PHY1Example they can optionally pass in the phy_name and phy_group_name as parameters.
3) makePhy can be called inside of a high level PHY_PHY2Example that calls PHY1Example. If makePhy is also called inside PHY1Example, then the lower level call will actually not execute and instead return the phy for PHY2Example.

This allows a lot of flexibility in how PHYs are created, and should make PHYs "just work" in most cases.
"""

class IPhy(object):

    """
    Returns list of callable phy functions
    """
    @abstractmethod
    def getPhyList(self):
        functionList = list()
        for functionName, functionPointer in inspect.getmembers(self, predicate=inspect.ismethod):
                if str(functionName).lower().startswith('phy_'):  # Check if the function name starts with "phy_"
                    if isinstance(functionPointer, types.MethodType):
                        #functionList.append(self.__class__.__name__ + "." + functionName)
                        functionList.append(functionPointer)
        return functionList

    """
    Builds empty phy model
    """
    @abstractmethod
    def _makePhy(self, modem_model, profile, phy_description=None, phy_group_name=None, readable_name=None, act_logic='', tags='', phy_name=None, locked=False):
        #Check to see if a higher-level PHY has already been created higher in the stack
        existing_phy = self.__get_phy_already_created(modem_model)
        if existing_phy == None:
            # Build phy from name, version, and class path
            if phy_name is None:
                #Use name of method if no phy name given
                phy_name = self.__highest_caller_phy()
            if phy_description is None:
                if readable_name is None:
                    phy_description = phy_name
                else:
                    phy_description = readable_name
            if phy_group_name is None:
                # Use file name if no group name given
                phy_group_name = self.__highest_caller_group()
            if readable_name is None:
                readable_name = phy_name.replace("_", " ")
            if tags is None:
                tags = ""
            if '_prod' in phy_name.lower():
                #If this is a PROD PHY, then also get the name of the PHY that the PROD PHY points to
                phy_points_to = self.__get_points_to_phy()
            else:
                phy_points_to = None

            if hasattr(self, 'phy_guids') and (modem_model.part_family, phy_name) in self.phy_guids:
                guid = self.phy_guids[modem_model.part_family, phy_name]
            else:
                guid = None

            phy = ModelPhy(phy_name, phy_description, profile, phy_group_name, readable_name=readable_name, act_logic=act_logic, tags=tags, phy_points_to = phy_points_to, locked=locked, guid=guid)
            modem_model.phys.append(phy)
            return phy
        else:
            #Return the already existing PHY
            return existing_phy

    """
    Helper methods
    """

    def __highest_caller_phy(self):
        #Get the call stack and go through it in reverse order, looking for any entry with PHY_ in its name
        stack = inspect.stack()
        for entry in reversed(stack):
            caller_name = entry[3]
            if caller_name.startswith("PHY_"):
                return caller_name #Return the highest level caller with PHY_ in its name

        #If we did not find a caller name then raise an exception
        raise AssertionError('Did not find a PHY method to name the PHY, check that the method is named correctly')

    def __highest_caller_group(self):
        #Get the call stack and go through it in reverse order, looking for any entry with PHY_ in its name
        stack = inspect.stack()
        for entry in reversed(stack):
            caller_name = entry[3]
            if caller_name.startswith("PHY_"):
                file_path = entry[1]
                file_name = os.path.basename(file_path)
                file_name_no_ext = os.path.splitext(file_name)[0]
                return file_name_no_ext #Return the file name of the highest level caller with PHY_ in its name

        #If we did not find a caller name then raise an exception
        raise AssertionError('Did not find a PHY method to name the PHY group, check that the method is named correctly')

    def __get_phy_already_created(self,model):
        #Return the already created phy object
        stack = inspect.stack()
        for entry in reversed(stack):
            caller_name = entry[3]
            if caller_name.startswith("PHY_"):
                try:
                    #Look for the PHY as an object in model.phys
                    phy = getattr(model.phys, caller_name)
                    return phy
                except AttributeError:
                    #If the PHY isn't in the model yet, then return None
                    return None
        #If we did not find the phy as already created then return None
        return None

    def __get_points_to_phy(self):
        # Get the call stack and go through it in reverse order, looking for a PROD PHY
        found_prod_phy = False
        stack = inspect.stack()
        for entry in reversed(stack):
            caller_name = entry[3]
            if caller_name.startswith("PHY_") and "_prod" in caller_name.lower():
                #We found a PROD PHY
                found_prod_phy = True
            elif caller_name.startswith("PHY_") and found_prod_phy:
                #If we previously found a PROD PHY, then the next PHY down in the stack is the "points to" PHY
               return caller_name

        return None
