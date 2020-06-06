invDet = 1.0 / (planeX * dirY - dirX * planeY); //required for correct matrix multiplication

transformX = invDet * (dirY * spriteX - dirX * spriteY);
transformY = invDet * (-planeY * spriteX + planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

spriteScreenX = int((w / 2) * (1 + transformX / transformY));

//calculate height of the sprite on screen
spriteHeight = abs(int(h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
//calculate lowest and highest pixel to fill in current stripe
drawStartY = -spriteHeight / 2 + h / 2;
if (drawStartY < 0) drawStartY = 0;
drawEndY = spriteHeight / 2 + h / 2;
if (drawEndY >= h) drawEndY = h - 1;

//calculate width of the sprite
spriteWidth = abs( (h / (transformY)));
drawStartX = -spriteWidth / 2 + spriteScreenX;
if (drawStartX < 0) drawStartX = 0;
drawEndX = spriteWidth / 2 + spriteScreenX;
if (drawEndX >= w) drawEndX = w - 1;