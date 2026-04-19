import sys
import os
from pathlib import Path

current_dir = Path(__file__).parent.absolute()
sys.path.append(str(current_dir))
sys.path.append(str(current_dir / "core"))

from fastapi import FastAPI, Request, Form
from fastapi.responses import HTMLResponse, RedirectResponse
from fastapi.templating import Jinja2Templates

try:
    from core.service import CarService
except ImportError:
    from core.service import CarService

app = FastAPI()
templates = Jinja2Templates(directory="templates")
service = CarService()

@app.get("/", response_class=HTMLResponse)
async def index(request: Request):
    status = service.get_status()
    # Исправленная строка:
    return templates.TemplateResponse(
        request=request, 
        name="index.html", 
        context={"status": status}
    )

@app.post("/action/start")
async def start_engine():
    service.start_engine()
    return RedirectResponse(url="/", status_code=303)

@app.post("/action/drive")
async def drive(direction: str = Form(...)):
    try:
        service.drive(direction)
        print(f"Команда получена: {direction}") 
    except Exception as e:
        print(f"Ошибка движения: {e}")
    return RedirectResponse(url="/", status_code=303)

@app.post("/action/stop")
async def stop_engine():
    service.stop_engine()
    return RedirectResponse(url="/", status_code=303)

@app.post("/action/refuel")
async def refuel(amount: float = Form(...)):
    service.refuel(amount)
    return RedirectResponse(url="/", status_code=303)

@app.post("/action/oil")
async def check_oil():
    service.check_oil()
    return RedirectResponse(url="/", status_code=303)

@app.post("/action/driver")
async def change_driver(name: str = Form(...)):
    service.change_driver(name)
    return RedirectResponse(url="/", status_code=303)

@app.post("/action/save")
async def save_data():
    from core.Entities import SaveManager
    SaveManager.save(service.car, service.driver, service.gas_station)
    service.last_message = "Данные успешно сохранены в файл!"
    return RedirectResponse(url="/", status_code=303)