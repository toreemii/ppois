from Entities import Fuel

class Engine:
    def __init__(self, fuel: Fuel, volume: float, power: int, oil: float):
        self.fuel = fuel
        self.volume = volume
        self.power = power
        self.oil = oil
        self.launched = False
        
    def start_engine(self) :
        self.launched = True

    def end_engine(self):
        self.launched = False

    def get_launched(self) -> bool:
        return self.launched
