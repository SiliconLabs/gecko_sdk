from functools import wraps


def phy_guid(guid):
    def inner_decorator(f):
        @wraps(f)
        def wrapped(*args, **kwargs):
            # print('before function')
            class_ref = args[0]
            model = args[1]
            if not hasattr(class_ref, 'phy_guids') or class_ref.phy_guids is None:
                class_ref.phy_guids = dict()
            class_ref.phy_guids[model.part_family, f.__name__] = guid
            response = f(*args, **kwargs)
            # print('after function')
            return response
        # print('decorating', f, 'with argument', guid)
        # wrapped.phy_guid = guid
        setattr(wrapped, 'phy_guid', guid)
        return wrapped
    return inner_decorator

def do_not_inherit_phys(cls):

    # Get a list of all of the PHY methods in the class (including inherited)
    inherited_methods = cls().getPhyList()
    inherited_method_names = [method.__name__ for method in inherited_methods]

    # Get a list of methods locally defined in the child class
    child_methods = cls.__dict__.items()
    child_method_names = [method[0] for method in child_methods if 'phy_' in method[0].lower()]

    # Form a list of methods we need to pass
    pass_method_names = [inherited_method_name for inherited_method_name in inherited_method_names if
                         inherited_method_name not in child_method_names]

    # Now add each pass method to the class
    for method_name in pass_method_names:
        setattr(cls, method_name, _phypass)

    return cls

def _phypass(self, model, phy_name=None):
    pass
