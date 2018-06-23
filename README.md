# Seacraft simulation

## Description
this program is a time-bound seacraft simultation.
the "world" is an unlimited sized sea.  
objects in the sea can be
* Ports
* Cruisers (pirate ships)
* Freighters
* patrol boats

each time pulse is equivalent to one hour.
with each time pulse, all objects in sea are updated.

#### Port
A port has a fixed position and fuel reservoir. It's responisble to load unload and refuel seacrafts.  
Each port has a fixed fuel production rate.  

#### Cruiser
A Pirate ship can attack a Freighter and take its containers,  
or attack a patrol boat and harm it's resistance. it cannot dock at a port, or refuel.  
A Cruiser's destination can be set to an angle, a point, or a port's direction   

#### Freighter
A freighter ship can sail from port to port, set a point in the sea or an angle.   
it has a "strength" that represents it's resistance from an attack by a pirate ship.  
optional: it can load and unload cargo at ports.  

#### Patrol boat
the patrol boat travels between ports.
after reaching it's given destination, it calculates the closest port that hasn't  
been visited yet and travel to it.  
after visiting all ports it travels back to its original destination port and stops there.  
every docking at port takes 3 time updates. at the first the ship gets an option to  
refuel if port's refuel queue is empty. at the second it rests, and at the third  
it prepares for it's next sail.  
A Patrol boat's destination can be set to an angle, a point, or a port.  

## Time pulses
With each time pulse the "world" is updated as following:  
#### Port
updates ports fuel amount and refuels a ship if needed
#### Cruiser
updates ships location and attacks ship if an attack request was set
#### Freighter
* if ship is does not have enough fuel to finish current update: it stops where the fuel ran out  
* if ship is headed to port:
  * if destination port is in reach: it's location is set to the port's location and it's status is updated to "docked".  
  * if not: ship's location is set according to course.  
* if ship is headed to given point:
  * if point is in reach: it's location is set to the point's location and it's status is updated to stopped.  
  * if not: ship's location is set according to course.  
* if ship is stopped or out of fuel: no update takes place.
#### Patrol boat
* if ship is does not have enough fuel to finish current update: it stops where the fuel ran out
* if ship's destination port is in reach: ship's location is updated to be ports location.
  * if the patrol boat finished visiting all ports: status is set to "stopped"
  * if not: status is set to "docked" visit time is set to 0 (out of 3)
* if ship's destination is not in reach: ship continues on course
* if ship is docked:
  * if current port was set a docking port: ship's status is set to "stopped"
  * if visit time reached 3: closest port is set as next destination and ship prepares for sail
* if ship's status is stopped or out of fuel: do nothing
# Class diagram
![uml](https://github.com/mantinband/seacraft-simulation/blob/master/class-uml.jpg?raw=true)
