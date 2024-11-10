---- AUTOMATIC MEDICINE DISPENSER ----

PROJECT OVERVIEW:

The Automatic Medicine Dispenser System is designed to manage multiple
containers, each holding a specific type of medicine. The system allows users to
refill, dispense, and monitor medicines in containers, where each container
holds medicines in a queue (FIFO). Each container also has a dispensing time and
alerts when the medicine quantity is low. The system has various features like
setting dispensing times, refilling medicine, and displaying information about
the containers.

--------------------------------------------------------------------------------------

ASSUMPTIONS AND LIMITATIONS:

- No Real-Time Clock: The system requires manual input of the current time for
dispensing at a set time. It lacks integration with an actual clock.

- Medicine Representation: Medicines are represented by a single character
('O'), which may not be intuitive.

- Lack of Database Integration: Medicine and dispense information are stored
only in memory. If the program exits or crashes, all data will be lost.

- User Inputs: The user will always provide inputs in the expected format (e.g.,
valid container numbers, valid time in HH:MM:SS format).

- No Concurrent Operations: The system assumes that only one operation is being
executed at any given time (e.g., refilling and dispensing are not
simultaneous).

--------------------------------------------------------------------------------------

ALGORITHM:

1. Initialization:
    
    -Create an array of containers, each containing a medicine name, front and
    rear pointers for a linked list (to represent medicine queue), a quantity count,
    a motor status (to indicate if the dispenser motor is on or off), and a
    dispense time.
    
    -Set all the containers to an initial state where no medicine is set,
    quantities are zero, and the motor is off. 

2. Display Instructions:

    -Display a menu with different options for the user: 
        1. Setup (Configure a container with medicine name and dispense time).
        2. Refill Medicine (Add medicine to a container). 
        3. Update Settings (Change medicine name, time, or reset a container). 
        4. View All Containers (Display current state of all containers). 
        5. Dispense Medicine at Set Time (Automatically dispense medicine based on pre-configured time). 
        6. Instruction Manual (Show the instruction manual again). 
        7. Exit (Exit the system).

    -Alert if the medicine quantity is low (below the threshold of 2).

3. Setup Function:

    -Prompt the user to choose a container (1 to 5). 
    
    -If the container is not yet set up, prompt the user to enter the medicine
    name and the dispense time (HH:MM:SS).
    
    -Validate the time format and ensure it is within a valid range (0-23
    for hours, 0-59 for minutes and seconds).

4. Refill Medicine:

    -Prompt the user to choose a container (1 to 5). 

    -Medicines are added as "O" (representing a medicine) to the container,
    following the FIFO structure.

    -Ensure that no more than 10 medicines are added to the container.

5.Update Settings:

    -User can change the medicine name, update the dispensing time, or reset the
    container.

    -Validate the choices and ensure that the reset functionality clears the
    container’s contents and settings.

6. View All Containers:

    -Display the details of each container, including:
        -Medicine name
        -Current quantity of medicines
        -Dispensing time 
        -Pictorial representation of medicines in the queue (FIFO format).
    
7. Dispense Medicine at Set Time:

    -User inputs the current time.

    -The system compares the current time with the dispensing time set for each
    container.

    -If the times match, the system turns on motor, automatically dispenses one
    medicine from the container and then turns off motor.

8. Low Quantity Alert:

    -Regularly checks if any container has a quantity below the defined
    threshold (2).

    -Alerts the user about the low quantity, prompting them to refill the
    container.

9. Exit System:

    -If the user selects "Exit", the system terminates.

---------------------------------------------------------------------------------