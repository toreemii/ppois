from Exceptions.CarException import CarException

class DifferentFuelException(CarException):
    def __init__(self, message: str = "Разное топливо."):
        super().__init__(message)