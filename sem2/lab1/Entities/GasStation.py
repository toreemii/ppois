from Entities.Fuel import Fuel
from Entities.Car import Car
from Exceptions.DifferentFuelException import DifferentFuelException
from Exceptions.FuelException import FuelException
from Exceptions.DeficitException import DeficitException

class GasStation :
    def __init__(self, fuel: Fuel, volume: float):
        self.fuel = fuel
        self.volume = volume
        
    def fill_fuel(self, car: Car, amount: float):
        if self.fuel != car.engine.fuel:
           raise DifferentFuelException()
        if (car.gastank.max_value < car.gastank.amount + amount):
            raise FuelException()
        if (self.volume - amount < 0):
            raise DeficitException()
        car.gastank.amount += amount
        self.volume -= amount
            
    
    