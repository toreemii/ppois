class Gastank :
    def __init__(self, amount: float, max_value: float):
        self.amount = amount
        self.max_value = max_value
        
    def get_amount(self) -> float:
        return self.amount
