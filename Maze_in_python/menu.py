import pygame
import sys
import webbrowser
import time
from main import *

pygame.init()
window = pygame.display.set_mode((1280, 720))
background = pygame.image.load("tlo.png")


class Button:

    def __init__(self, x_cord, y_cord, file):
        self.x_cord = x_cord
        self.y_cord = y_cord
        self.button_img = pygame.image.load(f"{file}.png")
        self.buttonh_img = pygame.image.load(f"{file}hover.png")
        self.hitbox = pygame.Rect(self.x_cord,self.y_cord,self.button_img.get_width(),self.button_img.get_height())

    def tick(self):
        if self.hitbox.collidepoint(pygame.mouse.get_pos()):
            if pygame.mouse.get_pressed()[0]:
                return True
            
    def draw(self, window):
        if self.hitbox.collidepoint(pygame.mouse.get_pos()):
            window.blit(self.buttonh_img,(self.x_cord,self.y_cord))
        else:
            window.blit(self.button_img,(self.x_cord,self.y_cord))


def menu():
    t = Timer()
    run = True
    image = pygame.image.load("graj.png")
    image_hover = pygame.image.load("grajhover.png")
    background_img = pygame.image.load("menuzdj.png")
    przycisk = Button(545,527,"graj")
    przycisk2 = Button(649,599,"strona")
    while run:
        pygame.time.Clock().tick(100)  # maksymalne klatki
        # Handle events / obsluga zdarzen czyli co sie dzieje
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
            elif event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                run = False

        if przycisk.tick():
            t.start()
            main()
        if przycisk2.tick():
            webbrowser.open("http://g-script.xyz/TheMaze/login.php")
        window.blit(background_img, (0, 0))
        przycisk.draw(window)
        przycisk2.draw(window)
        pygame.display.update()
