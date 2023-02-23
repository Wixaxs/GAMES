import pygame , sys
from wygrales import *
from zycia2 import *

pygame.init()
window = pygame.display.set_mode((1280, 720))
background = pygame.image.load("tlo.png")


class Health:

    def __init__(self, max_health=100):
        self.health = max_health
        self.max_health = max_health
        self.alive = True

    def dealt_damage(self,damage):
        self.health -= damage
        if self.health <= 0:
            self.health = 0
            self.alive = False

    def draw_health(self,win,x,y,max_width,height):
        percent_width = self.health / self.max_health
        width = round(max_width * percent_width)
        pygame.draw.rect(win,(30,30,30),(x,y,max_width,height))
        pygame.draw.rect(win,(30,250,25),(x,y,width,height))


class Physic:
    def __init__(self, x, y, width, height):
        self.x_cord = x
        self.y_cord = y
        self.width = width  # szerokosc
        self.height = height  # wysokosc
        self.previous_x = x
        self.previous_y = y
        self.hitbox = pygame.Rect(self.x_cord, self.y_cord, self.width, self.height)

    def physic_tick(self, beams,traps):
        self.hitbox = pygame.Rect(self.x_cord, self.y_cord, self.width, self.height)
        win = Win()
        for beam in beams:
            if beam.hitbox.colliderect(self.hitbox): # cofanie obeiktu do miejsca z poprzedniej klatki
                self.x_cord = self.previous_x
                self.y_cord = self.previous_y

        if win.hitbox.colliderect(self.hitbox):  # jezeli dotknie miejsca win
            wygrales()
        for trap in traps:
            if trap.hitbox.colliderect(self.hitbox): # jezeli dotknie pulapki
                Health.dealt_damage(self,1)

        self.previous_x = self.x_cord
        self.previous_y = self.y_cord


class Player(Physic,Health):
    def __init__(self):
        self.image = pygame.image.load("postac2.png")
        width = self.image.get_width()
        height = self.image.get_height()
        Health.__init__(self,100)
        Physic.__init__(self,550,320,width,height)
        self.hitbox = pygame.Rect(self.x_cord,self.y_cord,self.width,self.height)

    def tick(self, beams,traps):
        self.physic_tick(beams,traps)
        if not self.alive:
            przegrales()
        speed = 5
        keys = pygame.key.get_pressed()
        self.hitbox = pygame.Rect(self.x_cord, self.y_cord, self.width, self.height)
        if keys[pygame.K_w]:
            self.y_cord -= speed
        if keys[pygame.K_s]:
            self.y_cord += speed
        if keys[pygame.K_d]:
            self.x_cord += speed
        if keys[pygame.K_a]:
            self.x_cord -= speed

    def draw(self):
        window.blit(self.image, (self.x_cord, self.y_cord))
        self.draw_health(window,self.x_cord,self.y_cord - 15, self.width, 10)


class Beam:
    def __init__(self, x, y, width, height):
        self.image = pygame.image.load("ziemia.png")
        self.x_cord = x
        self.y_cord = y
        self.width = width
        self.height = height
        self.hitbox = pygame.Rect(self.x_cord, self.y_cord, self.width, self.height)

    def draw(self, win):
        pygame.draw.rect(win, (150, 150, 150), self.hitbox)


class Win:
    def __init__(self):
        self.x_cord = 30
        self.y_cord = 660
        self.width = 30
        self.height = 30
        self.window = window
        self.hitbox = pygame.Rect(self.x_cord,self.y_cord,self.width,self.height)

    def draw(self):
        pygame.draw.rect(self.window,(0,0,0),self.hitbox)


class Trap:
    def __init__(self,x,y,width,height):
        self.x_cord = x
        self.y_cord = y
        self.width = width
        self.height = height
        self.hitbox = pygame.Rect(self.x_cord,self.y_cord,self.width,self.height)

    def draw(self, window):
        pygame.draw.rect(window,(0,0,0),self.hitbox)

