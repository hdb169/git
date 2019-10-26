#2019 oct 25 Friday
#this is the macro for the  very beginning concepts of python 
print("basic stuffs in Python")
print ("Hello, I am learning python")

a =8
b =8.7
c = 9.09
print (" a = " ,a) #to print a
print (" a = " + str(a)) # u can use this too
print (" b = " + str(b))
print (" c = " + str(c))

#name = 'hem'
#print ('my name is {name}.')# this works only for python 3.6

x = 1089
print("The number is " + str(x))
print("The number is %s" % x)
print("The number is {0} and {0}".format(str(a))) # {zero}

y =35
print ("I am",y)#or
print ("I am " + str(y)) #or
print ("I am %s" %y) 

#To print, the data type must be the same. 
x = 10
print(x+4)
print(int(x)+4)
print("x plus 4 = ",int(x) + 4)
print(str(x) + " +" +  str(" what") + str(" will make 19"))# all are string type

#Code #1 : Simple demonstration of format()
# Python3 program to demonstarte the str.format() method 

print("{}, The computer science is the Great choice.".format("Hi Mr. Bhatt"))

print("{}, The computer science is the Great choice.".format(str("Hi Mr. Bhatt"))) # you dont need str here

apple = "This is Bidhan and Sakshi's {}" 
print(apple.format("Dad"))

print ("This is Biddan and Sakshi's {}.".format("Dad"))

bachha = "my daughter is {} years old"
print(bachha.format(8))

#Syntax : { } { } .format(value1, value2)
#always keep your string inside  ------------->  " " i.e. my_string = (" ......")
my_string = "{} is a good {}, but his brother is {}"
print (my_string.format("Ram","boy","naughty kid."))

#or you can do so

print(("{} is a good {}, but his brother is {} kid.").format("Ram","boy","naughty"))
print(("Hi my name is {} and I am learning {}, so I am {}.").format("Bhatt", "Python", "excited"))
print(("Today is {} {} {}, {}").format("October", "25", "2019","Friday."))

