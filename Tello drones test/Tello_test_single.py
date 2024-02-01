import time
from djitellopy import Tello

# Initialize the Tello drone
tello = Tello()

# Connect to the drone
tello.connect(wait_for_state=True)

# Take off
tello.takeoff()

# Ascend to a height of 20 units
tello.move_up(20)

# Perform a series of movements
tello.move_forward(30)
tello.move_back(30)
tello.move_left(20)
tello.move_right(20)

# Rotate the drone
tello.rotate_clockwise(90)
tello.rotate_counter_clockwise(90)

# Take a picture
tello.take_picture()

# Perform a flip
tello.flip(direction='forward')

# Ascend a bit more
tello.move_up(10)

# Spin around to get a 360 view
tello.rotate_clockwise(360)

# Descend to original height
tello.move_down(30)

# Land
tello.land()

# Close the connection
tello.end()
