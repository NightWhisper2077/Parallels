To build using make, you need to specify float or double, depending on which type you need, for example: make float.
To build via cmake, you need to enable or disable the flag Double, depending on which type you need, for example: cmake -DDouble=On/OFF.
The answer for float is: -0.027786
The answer for double is: 4.8958202475108905e-11.
The assignment implies that the sine values are either double or float, depending on the condition. 
At the same time, the amount must be stored in double/float. With different types of errors, such values arise. 
When debating the values, they differed slightly, but you can see that by 3-4 quarters the amount of float decreases faster and goes beyond minus, while double is close to zero
