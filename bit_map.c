			write(fd,"BM",2);
			write(fd1, HIGHT * WIDTH * 4 / 8, 4);
			write(fd1, 0, 4);
			write(fd1, 54, 4);
			write(fd1, 40, 4);
			write(fd1, WIDTH, 4);
			write(fd1, HIGHT, 4);
			write(fd1, 0, 2);
			write(fd1, 4, 2);
			write(fd1, 0, 4);
			write(fd1, 0, 4);
			write(fd1, 0, 4);
			write(fd1, 0, 4);
			write(fd1, 0, 4);
			write(fd1, 0, 4);