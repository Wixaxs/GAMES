import pygame
import sys
import csv
from Button import *

pygame.init()

# game settings
window = pygame.display.set_mode((1920, 1080))
fps = 60
clock = pygame.time.Clock()
tile_size = 64
tile_types = 2
ROWS = 17
COLS = 30
bg = pygame.image.load('img/map/background.png').convert_alpha()
island = pygame.image.load('img/map/island.png').convert_alpha()
quit_btn = pygame.image.load('img/buttons/wyjdz.png').convert_alpha()
reset_btn = pygame.image.load('img/buttons/restart.png').convert_alpha()
w_win = pygame.image.load('img/win/w.png').convert_alpha()
g_win = pygame.image.load('img/win/g.png').convert_alpha()
lshift = pygame.image.load('img/menu/shiftl.png').convert_alpha()
lshift1 = pygame.image.load('img/menu/shiftl2.png').convert_alpha()
pshift = pygame.image.load('img/menu/shiftp.png').convert_alpha()
pshift2 = pygame.image.load('img/menu/shiftp2.png').convert_alpha()
tlo_menu = pygame.image.load('img/menu/tlo.png').convert_alpha()
img_list = []
for x in range(tile_types):
    img = pygame.image.load(f'img/map/{x}.png').convert_alpha()
    img_list.append(img)

class World():
    def __init__(self):
        self.obstacle_list = []

    def process_data(self, data):
        for y, row in enumerate(data):
            for x, tile in enumerate(row):
                if tile >= -1:
                    img = img_list[tile]
                    img_rect = img.get_rect()
                    img_rect.x = x * 64
                    img_rect.y = y * 64
                    tile_data = (img, img_rect)
                    if tile > -1:
                        self.obstacle_list.append(tile_data)

    def draw(self):
        for tile in self.obstacle_list:
            window.blit(tile[0], tile[1])


class Player(pygame.sprite.Sprite):
    def __init__(self, image, x, y):
        self.image = pygame.image.load(f'img/characters/{image}0.png').convert_alpha()
        self.rect = self.image.get_rect()
        self.rect.center = (x, y)
        self.speed = 1
        self.flip = False
        self.vel_y = 0
        self.gravity = 0.05
        self.in_air = True
        self.direction = 1
        self.width = self.image.get_width()
        self.height = self.image.get_height()
        self.alive = True
        self.health = 100
        self.shoot_cd = 0
        self.max_health = self.health
        self.file = image

    def move(self):
        dx = 0
        dy = 0
        key = pygame.key.get_pressed()
        if self.file == 'w':
            if key[pygame.K_d]:
                dx += self.speed
                self.flip = False
                self.direction = 1
            if key[pygame.K_a]:
                dx -= self.speed
                self.flip = True
                self.direction = -1
            if key[pygame.K_w] and self.in_air == False:
                self.vel_y = -5
                jump = False
                self.in_air = True
            if key[pygame.K_q]:
                self.shoot()

        if self.file == 'g':
            if key[pygame.K_l]:
                dx += self.speed
                self.flip = False
                self.direction = 1
            if key[pygame.K_j]:
                dx -= self.speed
                self.flip = True
                self.direction = -1
            if key[pygame.K_i] and self.in_air == False:
                self.vel_y = -5
                self.in_air = True
            if key[pygame.K_p]:
                self.shoot()


        self.vel_y += self.gravity
        if self.vel_y > 10:
            self.vel_y = 10
        dy += self.vel_y

        for tile in world.obstacle_list:
                if tile[1].colliderect(self.rect.x + dx, self.rect.y, self.width, self.height):
                    dx = 0
                if tile[1].colliderect(self.rect.x, self.rect.y + dy, self.width, self.height):
                    if self.vel_y < 0:
                        self.vel_y = 0
                        dy = tile[1].bottom - self.rect.top
                    elif self.vel_y >= 0:
                        self.vel_y = 0
                        self.in_air = False
                        dy = tile[1].top - self.rect.bottom
        if self.rect.colliderect(0, 1080, 2000, 1):
            self.alive = False

        self.rect.x += dx
        self.rect.y += dy

    def update_player(self):
        self.alive_check()
        if self.shoot_cd > 0:
            self.shoot_cd -= 1

    def alive_check(self):
        if self.health <= 0:
            self.health = 0
            self.speed = 0
            self.alive = False

    def shoot(self):
        if self.shoot_cd == 0:
            self.shoot_cd = 400
            bullet = Bullet(self.rect.centerx + (50 * self.direction), self.rect.centery, self.direction, self.file)
            bullet_group.add(bullet)

    def draw(self):
        window.blit(pygame.transform.flip(self.image, self.flip, False), self.rect)

class HealthBar():
    def __init__(self, x, y, health, max_health):
        self.x = x
        self.y = y
        self.health = health
        self.max_health = max_health

    def draw(self, health):
        #update with new health
        self.health = health
        #calculate health ratio
        ratio = self.health / self.max_health
        pygame.draw.rect(window, (0,0,0), (self.x - 2, self.y - 2, 154, 24))
        pygame.draw.rect(window, (255, 0, 0), (self.x, self.y, 150, 20))
        pygame.draw.rect(window, (0, 255, 0), (self.x, self.y, 150 * ratio, 20))


class Bullet(pygame.sprite.Sprite):
    def __init__(self, x, y, direction, file):
        pygame.sprite.Sprite.__init__(self)
        self.speed = 3
        self.image = pygame.image.load(f'img/bullets/{file}.png')
        self.rect = self.image.get_rect()
        self.rect.center = (x, y)
        self.direction = direction
    def update(self):
        self.rect.x += (self.direction * self.speed)
        if self.rect.right < 0 or self.rect.left > 1920:
            self.kill()
        for tile in world.obstacle_list:
            if tile[1].colliderect(self.rect):
                self.kill()
        if pygame.sprite.spritecollide(player1, bullet_group, False):
            if player1.alive:
                player1.health -= 5
                self.kill()
        if pygame.sprite.spritecollide(player2, bullet_group, False):
            if player2.alive:
                player2.health -= 5
                self.kill()

def reset():
    bullet_group.empty()

    data = []
    for row in range(ROWS):
        r = [-1] * COLS
        data.append(r)

    return data

bullet_group = pygame.sprite.Group()
world_data = []

for row in range(ROWS):
    r = [-1] * COLS
    world_data.append(r)

with open('img/map/map.csv', newline='') as csvfile:
    reader = csv.reader(csvfile, delimiter=',')
    for x, row in enumerate(reader):
        for y, tile in enumerate(row):
            world_data[x][y] = int(tile)

world = World()
world.process_data(world_data)
run = True
player1 = Player('w', 150, 50)
player2 = Player('g', 1650, 50)
health_bar1 = HealthBar(10, 10, player1.health, player1.health)
health_bar2 = HealthBar(1750, 10, player2.health, player2.health)
exit_button = Button(750, 800, quit_btn, 1)
reset_button = Button(1050, 800, reset_btn, 1)
key = pygame.key.get_pressed()
choice1 = False
choice2 = False
start = False
while run:
    if start == False:
        window.blit(tlo_menu, (0, 0))
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit(0)
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    sys.exit()
                if event.key == pygame.K_e:
                    start = True

    else:

        window.fill((226, 175, 193))
        world.draw()
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit(0)
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    sys.exit()

        bullet_group.update()
        bullet_group.draw(window)

        if player2.alive:
            health_bar2.draw(player2.health)
            player2.draw()
            player2.move()
            player2.alive_check()
            player2.update_player()
        else:
            window.blit(w_win, (0, 0))
            if exit_button.draw(window):
                sys.exit()
            if reset_button.draw(window):
                reset()
                world_data = reset()
                with open('img/map/map.csv', newline='') as csvfile:
                    reader = csv.reader(csvfile, delimiter=',')
                    for x, row in enumerate(reader):
                        for y, tile in enumerate(row):
                            world_data[x][y] = int(tile)
                world = World()
                world.process_data(world_data)
                player1 = Player('w', 150, 50)
                player2 = Player('g', 1650, 50)

        if player1.alive:
            health_bar1.draw(player1.health)
            player1.draw()
            player1.move()
            player1.alive_check()
            player1.update_player()
        else:
            window.blit(g_win, (0, 0))
            if exit_button.draw(window):
                sys.exit()
            if reset_button.draw(window):
                reset()
                world_data = reset()
                with open('img/map/map.csv', newline='') as csvfile:
                    reader = csv.reader(csvfile, delimiter=',')
                    for x, row in enumerate(reader):
                        for y, tile in enumerate(row):
                            world_data[x][y] = int(tile)
                world = World()
                world.process_data(world_data)
                player1 = Player('w', 150, 50)
                player2 = Player('g', 1650, 50)

    pygame.display.update()

