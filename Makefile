# Makefile for building the convert program

CC = gcc
CFLAGS = -Wall

all: convert

convert: main.o cmdLineInterpreter.o conversion.o
	$(CC) -o convert main.o cmdLineInterpreter.o conversion.o
main.o: main.c cmdLineInterpreter.h
	$(CC) $(CFLAGS) -c main.c 

cmdLineInterpreter.o: cmdLineInterpreter.c cmdLineInterpreter.h conversion.h
	$(CC) $(CFLAGS) -c cmdLineInterpreter.c

conversion.o: conversion.c conversion.h
	$(CC) $(CFLAGS) -c conversion.c  
