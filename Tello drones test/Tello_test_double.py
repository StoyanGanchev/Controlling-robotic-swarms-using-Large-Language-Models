import time
from djitellopy import Tello

# Initialize two Tello drones
tello1 = Tello()
tello2 = Tello()

# Connect to the drones
tello1.connect(wait_for_state=True)
tello2.connect(wait_for_state=True)

# Take off both drones
tello1.takeoff()
tello2.takeoff()

# Ascend to different heights
tello1.move_up(20)
tello2.move_up(30)

# Perform different movements
tello1.move_forward(30)
tello2.move_left(20)

tello1.move_back(30)
tello2.move_right(20)

# Rotate the drones
tello1.rotate_clockwise(90)
tello2.rotate_counter_clockwise(90)

# Take a picture with each drone
tello1.take_picture()
tello2.take_picture()

# Perform flips
tello1.flip(direction='forward')
tello2.flip(direction='backward')

# Ascend a bit more
tello1.move_up(10)
tello2.move_up(15)

# Spin around
tello1.rotate_clockwise(360)
tello2.rotate_counter_clockwise(360)

# Descend to original height
tello1.move_down(30)
tello2.move_down(45)

# Land both drones
tello1.land()
tello2.land()

# Close the connections
tello1.end()
tello2.end()
