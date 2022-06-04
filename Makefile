gfiles=client/image/stb_image.cpp client/land/load.cpp client/unit.cpp client/3d/glad/glad.c client/3d/model.cpp client/3d/object.cpp client/network/net.c client/ai/man.cpp client/collision.cpp
glink=-lm -lglfw -ldl
sfiles=server/utile/file.c server/net/host.c server/unit.c server/acount.c server/net/send.c server/net/recv.c
lfiles=

g:
	g++ -g client/main.cpp $(gfiles) $(gflags) -o empireExpense $(glink)

s:
	gcc -g server/main.c $(sfiles) -o serv

l:
	gcc land/generate_land.c -o land
