import pygame
import random

class Pacman:
    def __init__(self, x, y, config):
        
        self.rect = pygame.Rect(x + 2, y + 2, 26, 26) 
        self.speed = config['player']['speed']
        self.direction = pygame.Vector2(0, 0)
        self.next_direction = pygame.Vector2(0, 0)
        self.tile_size = 30 

    def update(self, walls):
        
        if self.direction.x != 0:
            target_y = (self.rect.centery // self.tile_size) * self.tile_size + self.tile_size // 2
            if self.rect.centery < target_y: self.rect.y += 1
            elif self.rect.centery > target_y: self.rect.y -= 1
            
        
        if self.direction.y != 0:
            target_x = (self.rect.centerx // self.tile_size) * self.tile_size + self.tile_size // 2
            if self.rect.centerx < target_x: self.rect.x += 1
            elif self.rect.centerx > target_x: self.rect.x -= 1
        
        if self.next_direction != pygame.Vector2(0, 0):
            
            test_rect = self.rect.move(self.next_direction * self.speed)
            if test_rect.collidelist(walls) == -1:
                
                if (self.rect.centerx % self.tile_size in range(13, 18) and 
                    self.rect.centery % self.tile_size in range(13, 18)):
                    self.direction = self.next_direction

        if self.direction != pygame.Vector2(0, 0):
            if self.rect.move(self.direction * self.speed).collidelist(walls) == -1:
                self.rect.move_ip(self.direction * self.speed)
            else:
                self.direction = pygame.Vector2(0, 0)

    def draw(self, screen):
        pygame.draw.circle(screen, (255, 255, 0), self.rect.center, 13)
        eye_dir = self.direction if self.direction.length() > 0 else pygame.Vector2(1, 0)
        pygame.draw.circle(screen, (0, 0, 0), (int(self.rect.centerx + eye_dir.x * 8), int(self.rect.centery + eye_dir.y * 8)), 3)

class Ghost:
    def __init__(self, x, y, config, color, behavior="random"):
        self.rect = pygame.Rect(x + 2, y + 2, 26, 26)
        self.speed = config['ghosts']['speed']
        self.color = color
        self.behavior = behavior
        self.direction = pygame.Vector2(1, 0)

    def update(self, walls, pacman_pos):
        
        possible_dirs = []
        for d in [pygame.Vector2(0, 1), pygame.Vector2(0, -1), pygame.Vector2(1, 0), pygame.Vector2(-1, 0)]:
            if self.rect.move(d * self.speed).collidelist(walls) == -1:
                
                if d != -self.direction:
                    possible_dirs.append(d)

        if not possible_dirs: 
            possible_dirs = [d for d in [pygame.Vector2(0, 1), pygame.Vector2(0, -1), pygame.Vector2(1, 0), pygame.Vector2(-1, 0)] 
                             if self.rect.move(d * self.speed).collidelist(walls) == -1]

        if self.behavior == "chase" and possible_dirs:
            
            self.direction = min(possible_dirs, key=lambda d: pygame.Vector2(self.rect.move(d * self.speed).center).distance_to(pygame.Vector2(pacman_pos)))
        elif possible_dirs:
            
            if self.rect.move(self.direction * self.speed).collidelist(walls) != -1 or random.random() < 0.1:
                self.direction = random.choice(possible_dirs)

        
        if self.rect.move(self.direction * self.speed).collidelist(walls) == -1:
            self.rect.move_ip(self.direction * self.speed)

    def draw(self, screen):
        pygame.draw.rect(screen, self.color, self.rect, border_top_left_radius=12, border_top_right_radius=12)
        pygame.draw.circle(screen, (255, 255, 255), (self.rect.centerx - 5, self.rect.centery - 4), 4)
        pygame.draw.circle(screen, (255, 255, 255), (self.rect.centerx + 5, self.rect.centery - 4), 4)