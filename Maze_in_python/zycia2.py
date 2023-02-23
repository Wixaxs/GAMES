import pygame,sys
from main import *

pygame.init()
window = pygame.display.set_mode((1280,720))


class Button2:
    def __init__(self):
        self.x_cord = 500
        self.y_cord = 500
        self.button_img = pygame.image.load("wyjdz.png")
        self.buttonh_img = pygame.image.load("wyjdzhover.png")
        self.hitbox = pygame.Rect(self.x_cord, self.y_cord, self.button_img.get_width(), self.button_img.get_height())

    def tick(self):
        if self.hitbox.collidepoint(pygame.mouse.get_pos()):
            if pygame.mouse.get_pressed()[0]:
                return True

    def draw(self, window):
        if self.hitbox.collidepoint(pygame.mouse.get_pos()):
            window.blit(self.buttonh_img, (self.x_cord, self.y_cord))
        else:
            window.blit(self.button_img, (self.x_cord, self.y_cord))


class Timer():

    def __init__(self):
        self._start = 0

    def start(self):
        self._start = pygame.time.get_ticks()

    def current(self):
        return (pygame.time.get_ticks() - self._start)/1000


def przegrales():
    t = Timer()
    przycisk2 = Button2()
    text_img = pygame.font.Font.render(pygame.font.SysFont("arial", 48), "Twój czas: ",True,(155,155,155))
    text_image = pygame.font.Font.render(pygame.font.SysFont("arial", 48), str(t.current()),True,(155,155,155))
    background = pygame.image.load("stracileszycie.png")
    run = True
    while run:
    # Handle events / obluga zdarzen czyli co sie dzieje
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit(0)
            elif event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                run = False

        window.blit(background, (0, 0))
        window.blit(text_image,(660,400))
        window.blit(text_img,(420,400))
        przycisk2.draw(window)
        if przycisk2.tick():
            sys.exit(0)
        pygame.display.update()

