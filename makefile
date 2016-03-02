all: user registration

user: user.c
	gcc user.c -o user -I -Wall

registration: r.c p.c l.c
	gcc r.c p.c l.c -o registration -I -Wall
