from Exceptions.CarException import CarException

class FuelException(CarException):
    def __init__(self, message: str = "Переполнение бака."):
        super().__init__(message)