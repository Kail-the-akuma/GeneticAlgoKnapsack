# main.py
import pygame
import random
from color_utils import random_color, create_population
from grid_utils import draw_grid, draw_selected_color

# Constants
GRID_SIZE = 10  # Size of each grid cell
GRID_WIDTH = 50  # Number of cells in the width of the grid (for population display)
GRID_HEIGHT = 50  # Number of cells in the height of the grid (for population display)
POPULATION_SIZE = 50  # Number of random colors

def main():
    pygame.init()

    # Screen dimensions
    screen_width = 1024
    screen_height = 768
    screen = pygame.display.set_mode((screen_width, screen_height))
    pygame.display.set_caption('Color Grid')

    # Generate colors
    population = create_population(POPULATION_SIZE)
    selected_color = random.choice(population)  # Pick a random color from the population for display

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                return

        # Clear the screen
        screen.fill((255, 255, 255))

        # Draw population
        draw_grid(screen, GRID_SIZE, GRID_WIDTH, GRID_HEIGHT, population)

        # Draw selected color
        draw_selected_color(screen, selected_color)

        pygame.display.flip()

if __name__ == "__main__":
    main()
