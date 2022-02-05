#include "world.h"

int	ft_free_all(t_world *world)
{
	int	pid;

	pid = 0;
	free(world->hittabels);
	free(world->cam);
	free(world->lights);
	while (pid != -1)
		pid = wait(NULL);
	mlx_destroy_window(world->mlx, world->mlx_win);
	exit(EXIT_SUCCESS);
}
