#-------------------------------------------------------------------------------
# Name:        Langton's ant
# Purpose:
#
# Author:      Benjamin LOISON
#
# Created:     12/03/2019
# Copyright:   (c) Benjamin LOISON 2019
# Licence:     Please quote the author
#-------------------------------------------------------------------------------

# fourmi size: 1
# square size: 3

# fourmi format: (if look up)
# 
# @@@
# .@.
# .@.

from tkinter import *
import time

tkengine = Tk()

WINDOW_WIDTH, WINDOW_HEIGHT = 960, 540
canvas = Canvas(tkengine, width = WINDOW_WIDTH, height = WINDOW_HEIGHT, bg = "#FFFFFF")
canvas.pack()

currentScreen = [[False for x in range(WINDOW_WIDTH)] for y in range(WINDOW_HEIGHT)]

antX = (WINDOW_WIDTH // 2) // 3
antY = (WINDOW_HEIGHT // 2) // 3
antDirection = 0 # 0 up | 1 right | 2 bottom | 3 left

PT_SIZE = 3

def plot(x, y, color = "#000000"):
    global canvas
    canvas.create_line(x + 1, y + 1, x + 2, y + 2, fill = color)

def drawAnt():
    global canvas, antX, antY
    antXTmp = antX * PT_SIZE
    antYTmp = antY * PT_SIZE
    plot(antXTmp + 1, antYTmp + 1, "#FF0000")
    if antDirection == 0:
        plot(antXTmp + 1, antYTmp, "#FF0000")
        plot(antXTmp, antYTmp + 2, "#FF0000")
        plot(antXTmp + 1, antYTmp + 2, "#FF0000")
        plot(antXTmp + 2, antYTmp + 2, "#FF0000")
    elif antDirection == 1:
        plot(antXTmp - 1, antYTmp, "#FF0000")
        plot(antXTmp + 1, antYTmp, "#FF0000")
        plot(antXTmp + 1, antYTmp + 1, "#FF0000")
        plot(antXTmp + 1, antYTmp + 2, "#FF0000")
    elif antDirection == 2:
        plot(antXTmp + 1, antYTmp + 2, "#FF0000")
        plot(antXTmp, antYTmp, "#FF0000")
        plot(antXTmp + 1, antYTmp, "#FF0000")
        plot(antXTmp + 2, antYTmp, "#FF0000")
    elif antDirection == 3:
        plot(antXTmp + 1, antYTmp, "#FF0000")
        plot(antXTmp - 1, antYTmp, "#FF0000")
        plot(antXTmp - 1, antYTmp + 1, "#FF0000")
        plot(antXTmp - 1, antYTmp + 2, "#FF0000")

def fill(x0, y0):
    global canvas
    x0 *= PT_SIZE
    y0 *= PT_SIZE
    for j in range(y0, y0 + PT_SIZE):
        for i in range(x0, x0 + PT_SIZE):
            plot(i, j)

def display():
    while True:
        global antDirection, antX, antY
        #print(antX, antY)
        #for i in range(10**5): pass
        canvas.delete("all")
        for x in range(0, WINDOW_WIDTH):
            for y in range(0, WINDOW_HEIGHT):
                if currentScreen[y][x]:
                    fill(x + 1, y + 1)
        if currentScreen[antY][antX]: antDirection += 1
        else: antDirection -= 1
        antDirection %= 4
        currentScreen[antY][antX] = not currentScreen[antY][antX]
        if antDirection == 0: antY += 1
        elif antDirection == 1: antX += 1
        elif antDirection == 2: antY -= 1
        elif antDirection == 3: antX -= 1
        drawAnt()
        canvas.update()
        
tkengine.after(0, display)
tkengine.mainloop()