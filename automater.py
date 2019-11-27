import os


def main():
	print("---------------------------------------------------------------") 
	os.system("make")
	for i in range(0, 10000, 2000):
		print("running ./finalproject with", i, " bucket padding and password.txt")
		command = "./main password.txt " + str(i)
		os.system(command)
		print("---------------------------------------------------------------") 

	for i in range(0, 10000, 2000):
		print("running ./finalproject with", i, " bucket padding and names.txt")
		command = "./main names.txt " + str(i)
		os.system(command)
		print("---------------------------------------------------------------") 

	for i in range(0, 10000, 2000):
		print("running ./finalproject with", i, " bucket padding and names_big.txt")
		command = "./main names_big.txt " + str(i)
		os.system(command)
		print("---------------------------------------------------------------") 


main()