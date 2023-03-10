from pyradioconfig.parts.nerio.phys.Phys_Studio_Base_Sidewalk import Phys_Studio_Base_Sidewalk_Nerio


class Phys_Studio_Base_Sidewalk_Ocelot(Phys_Studio_Base_Sidewalk_Nerio):

    def _set_sidewalk_tolerances(self, model, phy):
        # Match Wi-SUN FSK specs
        phy.profile_inputs.baudrate_tol_ppm.value = 300
        phy.profile_inputs.rx_xtal_error_ppm.value = 20
        phy.profile_inputs.tx_xtal_error_ppm.value = 20
        phy.profile_inputs.deviation_tol_ppm.value = 300000

    def _timing_detection_optimization(self, phy):
        #No longer needed due to TRECS demodd
        pass
