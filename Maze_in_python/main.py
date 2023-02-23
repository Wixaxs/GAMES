import pygame , sys, math,time
from game import *
from menu import *

pygame.init()
window = pygame.display.set_mode((1280, 720))
background = pygame.image.load("tlo.png")


def main():
    clock = pygame.time.Clock()
    delta = 0.0
    run = True
    player = Player()
    win = Win()
    t = Timer()
    traps = [
        Trap(30,30,50,50),
        Trap(350,30,50,60),
        Trap(430,30,50,60),
        Trap(35,440,80,50),
        Trap(160,440,50,50),
        Trap(380,640,50,50),
        Trap(380,550,60,50),
        Trap(1180,540,70,50),
        Trap(1035,540,90,50),
        Trap(1035,450,50,50),
        Trap(1035,350,50,50)
    ]
    beams = [
        Beam(0,0,30,720),
        Beam(0,0,1280,30),
        Beam(1250,0,30,720),
        Beam(0,690,1280,30),
        Beam(130,0,30,100),
        Beam(0,130,60,30),
        Beam(400,0,30,120),
        Beam(250,105,300,30),
        Beam(300,110,30,200),
        Beam(130,200,300,30),
        Beam(550,105,30,80),
        Beam(650,105,500,30),
        Beam(1150,105,30,300),
        Beam(900,215,250,30),
        Beam(1000,405,180,30),
        Beam(1000,350,30,270),
        Beam(1000,500,250,30),
        Beam(1140,500,30,130),
        Beam(770,550,260,30),
        Beam(650,470,30,300),
        Beam(650,200,100,30),
        Beam(650,110,30,100),
        Beam(730,200,30,180),
        Beam(650,300,80,30),
        Beam(0,400,250,30),
        Beam(130,400,30,120),
        Beam(0,590,100,30),
        Beam(350,420,30,300),
        Beam(350,600,200,30),
        Beam(450,500,30,100)
    ]

    while run:
        # Handle events / obluga zdarzen czyli co sie dzieje
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit(0)
            elif event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                run = False


        # ticking
        delta += clock.tick()/1000.0
        while delta > 1 / 120:
            delta -=1 / 120

        for beam in beams:
            beam.draw(window)

            for trap in traps:
                trap.draw(window)
        t.start()
        win.draw()

        window.blit(pygame.image.load("tlozkrzakami.png"), (0, 0))
        player.tick(beams,traps)
        player.draw()
        pygame.display.update()

# if __name__ == "__main__":
#     menu()
