#data dictionary simplest example: 2020 jan 8
#dictionary is a key value pairs

#example 1

d={}
#d ={"hem": 30, "bidhan" :3, "sakshi":8}
d["hem"] = 30# hem is key and 30 is the value.
d["bidhan"] = 3
d["sakshi"]=8
print("hem is " +str(d["hem"])+" year's old.")

print(d["bidhan"])
d["bijaya"]=28
print(d["bijaya"])
print(d)
d["bijaya"]=35
d["debendra"]=40
print(d)
#how to iterate key_value_pair:
for key, value in d.items():
    print("key = " + str(key))
    print("value = " +str(value))
    print(" ")
print("done for Example 1.")


#Example 2

#facebook post
#user_id = 10
#message = "hello world"
#language = " English"
#datetime = "2020010810pm"
#location =  (44.23, 348.79)#tuples

#create dictionary
post= {" user_id":10, "message":"hello world", "langusge":"English", "datetime":"2020010810pm", "location":(44.23,348.79)}
print(post)
#There are 5 inputs and 5 outputs, inputs are called key and the outputs are called values.("key": values) pairs.
print(type(post))   #<class 'dict'> so dict is the class,  and we can make any dictionary by using dict.



#Example 3
post1=dict(message="hellow world, I am learning python.", language="English", time=1030)#here you do not need to keep "" in keys, but requires in values if it is a string.
print(post1)
print(type(post1))#{'message': 'hellow world', 'language': 'English', 'time': 1030},
# "" are being used when u print it.
# add any other key"value pair in the dictionary
post1['location']="F348"# But when u add any key value, use ""in key
post1["temp"] =20
print(post1)
print(post['message'])#hello world
print(post1['message'])#hellow world, I am learning python.
#lets print the value which does not exist in dictionary, post1

print(post1)
print(post)

print(dir(post1))#print the directory with different methods:, lets try the get method

for key in post1.keys():
    value = post1[key]#===================imp, 
    print(key, "=", value)
print( "\n******done*********\n")
for key, value in post1.items():
    print(key,"=",value)
 #pop and popitem method allows you to remove a single item inthe dictionary, but clear methos will remove all data  
print(dir(post1))#will give u this
'''
'temp': 20, 'language': 'English', 'time': 1030, 'message': 'hellow world, I am learning python.', 'location': 'F348'}
{'datetime': '2020010810pm', ' user_id': 10, 'langusge': 'English', 'message': 'hello world', 'location': (44.23, 348.79)}
['__class__', '__contains__', '__delattr__', '__delitem__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__getitem__', '__gt__', '__hash__', '__init__', '__iter__', '__le__', '__len__', '__lt__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__setitem__', '__sizeof__', '__str__', '__subclasshook__', 'clear', 'copy', 'fromkeys', 'get', 'items', 'keys', 'pop', 'popitem', 'setdefault', 'update', 'values']
'''
