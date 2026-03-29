import pygame
import json
import sys
import os
from entities import Pacman, Ghost

def load_config():
    try:
        with open('assets/config.json', 'r') as f:
            return json.load(f)
    except FileNotFoundError:
        print("Ошибка: assets/config.json не найден!")
        sys.exit()

CONFIG = load_config()

class Game:
    def __init__(self):
        pygame.init()
        try:
            pygame.mixer.pre_init(44100, -16, 2, 512)
            pygame.mixer.init()
            pygame.mixer.set_num_channels(8)
        except: pass

        self.screen = pygame.display.set_mode(
            (CONFIG['screen']['width'], CONFIG['screen']['height']), 
            pygame.RESIZABLE
        )
        pygame.display.set_caption("Pac-man: Elite Edition")
        self.clock = pygame.time.Clock()
        
        self.state = "MENU" 
        self.running = True
        self.current_level_file = "assets/level1.json"
        
        available = pygame.font.get_fonts()
        self.font_name = "impact" if "impact" in available else "arialblack"
        self.font_title = pygame.font.SysFont(self.font_name, 80)
        self.font_menu = pygame.font.SysFont(self.font_name, 42)
        self.font_ui = pygame.font.SysFont(self.font_name, 26)
        
        self.YELLOW, self.WHITE, self.BLUE = (255, 255, 0), (255, 255, 255), (33, 33, 255)
        self.GOLD, self.RED, self.ORANGE, self.PINK = (160, 140, 0), (255, 0, 0), (255, 165, 0), (255, 182, 193)
        self.CYAN, self.GREEN = (0, 255, 255), (0, 255, 0)
        
        self.menu_options = ["Карта 1", "Карта 2", "Таблица рекордов", "Справка", "Выход"]
        self.current_selection = 0
        self.user_name = ""
        self.is_new_record = False
        self.high_scores = [] 

        self.freeze_timer = 0
        self.boost_timer = 0
        self.normal_speed = CONFIG['player']['speed']
        self.powerups = []
        
        self.init_audio()
        self.reset_game()

    def init_audio(self):
        try:
            if os.path.exists(CONFIG['assets']['music']):
                pygame.mixer.music.load(CONFIG['assets']['music'])
                pygame.mixer.music.set_volume(0.2)
                pygame.mixer.music.play(-1)
        except: pass

        self.death_sound = None
        try:
            path_death = CONFIG['assets'].get('death_sound')
            if path_death and os.path.exists(path_death):
                self.death_sound = pygame.mixer.Sound(path_death)
        except: pass
        self.eat_sound = None

    def save_score_to_memory(self):
        name = self.user_name.strip() if self.user_name.strip() else "PLAYER"
        self.high_scores.append({"name": name, "score": self.score})
        self.high_scores = sorted(self.high_scores, key=lambda x: x['score'], reverse=True)[:10]

    def reset_game(self):
        self.score = 0
        self.user_name = ""
        self.is_new_record = False
        self.freeze_timer = 0
        self.boost_timer = 0
        self.walls, self.dots, self.ghosts, self.powerups = [], [], [], []
        
        if not pygame.mixer.music.get_busy(): 
            try: pygame.mixer.music.play(-1)
            except: pass
        
        try:
            with open(self.current_level_file, 'r') as f:
                layout = json.load(f)['layout']
            self.level_h_px, self.level_w_px = len(layout) * 30, len(layout[0]) * 30
            for r, row in enumerate(layout):
                for c, cell in enumerate(row):
                    x, y = c * 30, r * 30
                    if cell == "#": self.walls.append(pygame.Rect(x, y, 30, 30))
                    elif cell == ".": self.dots.append(pygame.Rect(x + 12, y + 12, 6, 6))
                    elif cell == "*":
                        p_type = "freeze" if (r + c) % 2 == 0 else "speed"
                        self.powerups.append({"rect": pygame.Rect(x + 6, y + 6, 18, 18), "type": p_type})
                    elif cell == "P": 
                        self.pacman = Pacman(x, y, CONFIG)
                        self.pacman.speed = self.normal_speed
                    elif cell == "G":
                        count = len(self.ghosts)
                        if "level2" in self.current_level_file:
                            if count == 0: color, beh = self.RED, "chase"
                            elif count == 1: color, beh = self.PINK, "chase"
                            else: color, beh = self.ORANGE, "random"
                        else:
                            color, beh = (self.RED, "chase") if count == 0 else (self.ORANGE, "random")
                        self.ghosts.append(Ghost(x, y, CONFIG, color, beh))
        except: pass

    def handle_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT: self.running = False
            if event.type == pygame.VIDEORESIZE:
                self.screen = pygame.display.set_mode((event.w, event.h), pygame.RESIZABLE)
            
            if self.state == "MENU":
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_UP: self.current_selection = (self.current_selection - 1) % len(self.menu_options)
                    elif event.key == pygame.K_DOWN: self.current_selection = (self.current_selection + 1) % len(self.menu_options)
                    elif event.key == pygame.K_RETURN: self.select_menu_option()
            
            elif self.state == "GAMEOVER":
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_RETURN:
                        self.save_score_to_memory()
                        self.reset_game()
                        self.state = "MENU"
                    elif event.key == pygame.K_BACKSPACE:
                        self.user_name = self.user_name[:-1]
                    else:
                        if len(self.user_name) < 10 and event.unicode.isprintable():
                            self.user_name += event.unicode.upper()

            elif self.state in ["HELP", "SCOREBOARD"]:
                if event.type == pygame.KEYDOWN and event.key in [pygame.K_ESCAPE, pygame.K_RETURN, pygame.K_SPACE]:
                    self.state = "MENU"

    def select_menu_option(self):
        opt = self.menu_options[self.current_selection]
        if opt in ["Карта 1", "Карта 2"]: 
            self.current_level_file = f"assets/level{1 if opt == 'Карта 1' else 2}.json"
            self.reset_game(); self.state = "GAME"
        elif opt == "Таблица рекордов": self.state = "SCOREBOARD"
        elif opt == "Справка": self.state = "HELP"
        elif opt == "Выход": self.running = False

    def finish_round(self, won):
        pygame.mixer.music.stop()
        if not won and self.death_sound:
            pygame.mixer.Channel(1).play(self.death_sound)
            pygame.time.delay(800)
        
        top_val = self.high_scores[0]['score'] if self.high_scores else -1
        self.is_new_record = self.score > top_val
        self.state = "GAMEOVER"

    def update(self):
        if self.state == "GAME" and self.pacman:
            if self.freeze_timer > 0: self.freeze_timer -= 1
            if self.boost_timer > 0:
                self.boost_timer -= 1
                if self.boost_timer <= 0: self.pacman.speed = self.normal_speed

            keys = pygame.key.get_pressed()
            if keys[pygame.K_UP]: self.pacman.next_direction = pygame.Vector2(0, -1)
            if keys[pygame.K_DOWN]: self.pacman.next_direction = pygame.Vector2(0, 1)
            if keys[pygame.K_LEFT]: self.pacman.next_direction = pygame.Vector2(-1, 0)
            if keys[pygame.K_RIGHT]: self.pacman.next_direction = pygame.Vector2(1, 0)

            self.pacman.update(self.walls)
            
            for p in self.powerups[:]:
                if self.pacman.rect.colliderect(p['rect']):
                    if p['type'] == "freeze": self.freeze_timer = 300
                    else: 
                        self.pacman.speed = self.normal_speed * 1.8
                        self.boost_timer = 300
                    self.powerups.remove(p)
                    self.score += 50

            for d in self.dots[:]:
                if self.pacman.rect.inflate(10, 10).colliderect(d):
                    self.dots.remove(d); self.score += 10

            for g in self.ghosts:
                if self.freeze_timer <= 0:
                    g.update(self.walls, self.pacman.rect.center)
                if self.pacman.rect.colliderect(g.rect):
                    self.finish_round(won=False)
                    return

            if not self.dots and not self.powerups:
                self.finish_round(won=True)

    def draw(self):
        self.screen.fill((0, 0, 0))
        win_w, win_h = self.screen.get_size()
        center_x = win_w // 2
        
        if self.state == "MENU":
            title = self.font_title.render("PAC-MAN", True, self.YELLOW)
            self.screen.blit(title, title.get_rect(center=(center_x, 100)))
            for i, o in enumerate(self.menu_options):
                is_act = (i == self.current_selection)
                surf = self.font_menu.render(o, True, self.YELLOW if is_act else self.GOLD)
                rect = surf.get_rect(center=(center_x, 250 + i * 65))
                if is_act: pygame.draw.rect(self.screen, self.YELLOW, rect.inflate(40, 15), 3, border_radius=12)
                self.screen.blit(surf, rect)

        elif self.state == "HELP":
            t = self.font_title.render("СПРАВКА", True, self.YELLOW)
            self.screen.blit(t, t.get_rect(center=(center_x, 80)))
            
            lines = [
                "ЦЕЛЬ: СОБРАТЬ ВСЕ ТОЧКИ В ЛАБИРИНТЕ",
                "СТРЕЛКИ - УПРАВЛЕНИЕ ПАКМАНОМ",
                "БИРЮЗОВЫЙ ШАР - ЗАМОРОЗКА ВРАГОВ",
                "ЗЕЛЕНЫЙ ШАР - УСКОРЕНИЕ ИГРОКА",
                "SPACE - ВЕРНУТЬСЯ В МЕНЮ"
            ]
            for i, line in enumerate(lines):
                s = self.font_ui.render(line, True, self.WHITE)
                self.screen.blit(s, s.get_rect(center=(center_x, 220 + i * 50)))

        elif self.state == "SCOREBOARD":
            t = self.font_title.render("РЕКОРДЫ", True, self.YELLOW)
            self.screen.blit(t, t.get_rect(center=(center_x, 80)))
            if not self.high_scores:
                empty = self.font_ui.render("ПОКА ПУСТО", True, self.WHITE)
                self.screen.blit(empty, empty.get_rect(center=(center_x, 250)))
            else:
                for i, s in enumerate(self.high_scores[:7]):
                    txt = self.font_ui.render(f"{i+1}. {s['name']} - {s['score']}", True, self.WHITE)
                    self.screen.blit(txt, txt.get_rect(center=(center_x, 180 + i * 45)))

        elif self.state in ["GAME", "GAMEOVER"]:
            off_x, off_y = (win_w - self.level_w_px) // 2, (win_h - self.level_h_px) // 2
            for w in self.walls: pygame.draw.rect(self.screen, self.BLUE, w.move(off_x, off_y), 2)
            for d in self.dots: pygame.draw.circle(self.screen, (255, 184, 151), (d.centerx + off_x, d.centery + off_y), 3)
            for p in self.powerups:
                c = self.CYAN if p['type'] == "freeze" else self.GREEN
                pygame.draw.circle(self.screen, c, (p['rect'].centerx + off_x, p['rect'].centery + off_y), 8)
            
            for g in self.ghosts:
                old = g.rect.topleft; g.rect.topleft = (old[0] + off_x, old[1] + off_y)
                g.draw(self.screen); g.rect.topleft = old
            old_p = self.pacman.rect.topleft; self.pacman.rect.topleft = (old_p[0] + off_x, old_p[1] + off_y)
            self.pacman.draw(self.screen); self.pacman.rect.topleft = old_p
            
            self.screen.blit(self.font_ui.render(f"СЧЁТ: {self.score}", True, self.WHITE), (off_x, off_y - 40))

            if self.state == "GAMEOVER":
                ov = pygame.Surface((win_w, win_h), pygame.SRCALPHA); ov.fill((0, 0, 0, 215))
                self.screen.blit(ov, (0,0))
                
                is_win = len(self.dots) == 0 and len(self.powerups) == 0
                
                if is_win:
                    main_msg = "ПОБЕДА! ВСЁ СОБРАНО!"
                    color = self.GREEN
                elif self.is_new_record:
                    main_msg = "НОВЫЙ РЕКОРД!"
                    color = self.YELLOW
                else:
                    main_msg = "ИГРА ОКОНЧЕНА"
                    color = self.RED

                surf = self.font_title.render(main_msg, True, color)
                self.screen.blit(surf, surf.get_rect(center=(center_x, win_h // 2 - 80)))
                
                name_s = self.font_menu.render(f"ИМЯ: {self.user_name}|", True, self.WHITE)
                self.screen.blit(name_s, name_s.get_rect(center=(center_x, win_h // 2 + 20)))
                
                hint_s = self.font_ui.render("ENTER - В МЕНЮ", True, self.GOLD)
                self.screen.blit(hint_s, hint_s.get_rect(center=(center_x, win_h // 2 + 110)))

        pygame.display.flip()
          
    def run(self):
        while self.running:
            self.handle_events(); self.update(); self.draw()
            self.clock.tick(CONFIG['screen']['fps'])
        pygame.quit()

if __name__ == "__main__":
    game = Game(); game.run()