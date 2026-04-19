# README.md — Лабораторная работа №1  
**Взаимодействие водителя с автомобилем**

## Важные сущности

- автомобиль
- водитель
- топливо
- двигатель
- колеса
- трансмиссия
- тормоза
- световые индикаторы
- бензозаправочная станция

## Описание проекта

Консольная программа-симулятор автомобиля.  
Пользователь может:
- заводить/глушить двигатель
- ехать в разные стороны
- заправляться на АЗС
- проверять масло
- менять водителя
- заезжать на СТО
- сохранять и загружать состояние между запусками (JSON-файл)


## Основные классы 

### `Entities.Fuel` (Enum)
```python
type_92 = "92"
type_95 = "95"
type_98 = "98"
diesel = "diesel"
```

### `Entities.Brakes` (Enum)
```python
disc_brakes = "disc_brakes"
drum_brakes = "drum_brakes"
handbrake   = "handbrake"
```

### `Entities.Lights` (Enum)
```python
head_lights = "head_lights"
tail_lights = "tail_lights"
```

### `Entities.Transmission` (Enum)
```python
manual                = "manual"
automatic             = "automatic"
continuously_variable = "continuously_variable"
```

### `Entities.Wheel` (Enum)
```python
summer_tires     = "summer_tires"
winter_tires     = "winter_tires"
all_season_tires = "all_season_tires"
```

### `Entities.Engine`
**Атрибуты**
- `fuel: Fuel` — тип топлива
- `volume: float` — объём двигателя
- `power: int` — мощность
- `oil: float` — уровень масла
- `launched: bool` — запущен ли двигатель

**Методы**
- `start_engine()` — заводит двигатель
- `end_engine()` — глушит двигатель
- `get_launched() -> bool` — возвращает состояние

### `Entities.Gastank`
**Атрибуты**
- `amount: float` — текущее количество топлива
- `max_value: float` — максимальная ёмкость

**Методы**
- `get_amount() -> float`

### `Entities.Car`
**Атрибуты**
- `car_brand: str`
- `brakes: Brakes`
- `engine: Engine`
- `gastank: Gastank`
- `lights: Lights`
- `wheels: Wheel`
- `transmission: Transmission`

**Методы движения** (все просто печатают сообщение)
- `move_forward()`
- `move_backward()`
- `move_left()`
- `move_right()`

### `Entities.Driver`
**Атрибуты**
- `name: str`
- `car: Car`

**Методы**
- `check_oil() -> float` — возвращает уровень масла в двигателе машины

### `Entities.GasStation`
**Атрибуты**
- `fuel: Fuel` — какой бензин продаётся
- `volume: float` — сколько литров осталось на колонке

**Методы**
- `fill_fuel(car: Car, amount: float)`  
  Проверяет совпадение топлива, переполнение бака и наличие топлива на колонке.  
  Бросает:
  - `DifferentFuelException`
  - `FuelException` (переполнение)
  - `DeficitException` (не хватает на колонке)

### `Entities.Station`
**Методы**
- `maintenance()` — печатает «Неполадки улажены.»

### `Utility.SaveManager`
**Статические методы**
- `save(car, driver, gasstation)` — сохраняет состояние в `car_save.json`
- `load()` — загружает состояние. Если файла нет или он битый — возвращает дефолтные объекты

### Исключения (все наследуются от `CarException`)
- `DifferentFuelException` — разное топливо
- `FuelException` — переполнение бака
- `DeficitException` — дефицит топлива на АЗС
- `LoadException` — ошибка загрузки сохранения

При первом запуске создаётся `car_save.json` с начальным состоянием.

