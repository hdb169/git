#oct 28, 2019, Monday
#continue from one.py
print(("{} is a good {}, but his brother is {} kid.").format("Ram","boy","naughty"))
print(("Hi my name is {} and I am learning {}, so I am {}.").format("Bhatt", "Python", "excited"))
print(("Today is {} {} {}, {}").format("October", "25", "2019","Friday."))

#Syntax: {0}{1}.format(positional_argument,keyword_argument)
#Parameters : (positional_argument, keyword_argument)
#Positional_argument can be integers, floating point numeric constants, strings, characters and even variables.
#Keyword_argument is essentially a variable storing some value, which is passed as parameter.

# To demonstrate the use of formatters  with positional key arguments, Positional arguments are placed in order

print ("{0} love {1}!!".format("GeeksforGeeks","Geeks"))
#Reverse the index numbers with the parameters of the placeholders

print ("{1} love {0}  ".format("GeeksforGeeks", "Geeks"))

print("Every {} should know the use of {} {} programming and {}.".format("programmer","open", "Source", "operating systems"))
print("Every {3} should know the use of {2} {1} programming and {0}.".format("programmer","open", "Source", "operating systems"))
print("{gfg} is a {0} science portal for {1}".format("computer","geeks" , gfg = "GeeksforGeeks"))

""" is used for commemnt
s – strings
d – decimal integers (base-10)
f – floating point display
c – character
b – binary
o – octal
x – hexadecimal with lowercase letters after 9
X – hexadecimal with uppercase letters after 9
e – exponent notation
"""
#print ("The temperature outside is {0:d} degree celsius.".format(40.986))
print("The temperature today is {0:.0f} degrees outside !".format(35.567))
print("The temperature today is {0} degrees outside !".format(35.567))
print("marks obtained = {}%".format(77.89))
print("marks obtained = {0:.0f}%".format(77.89))
print("marks obtained = {0:.0f}%".format(78.89))  #0f = only whole numbers
print("marks obtained = {0:.1f}%".format(78.89))  #0f = only whole numbers
print("marks obtained = {0:.2f}%".format(78.892729782))  #0f = only whole numbers
print("marks obtained = {0:.3f}%".format(78.892729782))  #0f = only whole numbers


print("The {0} of 100 is {1:b}".format("binary", 100)) #convert integer to binary {1:b} is standard way
          
print("The {0} of 10 is {1:b}".format("binary", 10)) #convert integer to binary
print("The {0} of 18 is  {1:b}".format("binary", 18)) #convert integer to binary

print("The {0} of 30 is {1:b}".format("binary", 30))
