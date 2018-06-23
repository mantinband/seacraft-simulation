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

### Port
A port has a fixed position and fuel reservoir.  
It's responisble to load unload and refuel seacrafts.  
Each port has a fixed fuel production rate.  

### Cruiser
A Pirate ship can attack a Freighter and take its  
containers,or attack a patrol boat and harm it's  
resistance. it cannot dock at a port, or refuel.  
A Cruiser's destination can be set to an angle, a point,  
or a port's direction   

### Freighter
A freighter ship can sail from port to port,  
set a point in the sea or an angle. it has a "strength" that represents  
it's resistance from an attack by a pirate ship.  
optional: it can load and unload cargo at ports.  

### Patrol boat
the patrol boat travels between ports.  
after reaching it's given destination,  
it calculates the closest port that hasn't  
been visited yet and travel to it.  
after visiting all ports it travels back to   
its original destination port and stops there.  
every docking at port takes 3 time updates.  
at the first the ship gets an option to  
refuel if port's refuel queue is empty.  
at the second it rests, and at the third  
it prepares for it's next sail.  
A Patrol boat's destination can be set to an angle,   
a point, or a port.  

![uml](https://github.com/mantinband/seacraft-simulation/blob/master/class-uml.jpg?raw=true)
