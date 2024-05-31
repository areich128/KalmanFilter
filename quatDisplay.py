import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

def read_quaternions(file_path):
    with open(file_path, 'r') as file:
        quaternions = [np.fromstring(line.strip(), sep=',') for line in file if line.strip()]
    return quaternions

def update_quaternion(num, quaternions, line):
    q = quaternions[num]
    # Convert quaternion to rotation matrix
    R = quat_to_rot_matrix(q)
    # Apply rotation to a vector, here [1, 0, 0] for demonstration
    vector = R @ np.array([1, 0, 0])
    line.set_data([0, vector[0]], [0, vector[1]])
    line.set_3d_properties([0, vector[2]])
    return line,

def quat_to_rot_matrix(q):
    """ Convert a quaternion into a rotation matrix. """
    w, x, y, z = q[3], q[0], q[1], q[2]
    return np.array([
        [1 - 2*y*y - 2*z*z,     2*x*y - 2*z*w,       2*x*z + 2*y*w],
        [2*x*y + 2*z*w,         1 - 2*x*x - 2*z*z,   2*y*z - 2*x*w],
        [2*x*z - 2*y*w,         2*y*z + 2*x*w,       1 - 2*x*x - 2*y*y]
    ])

# Load quaternions from file
quaternions = read_quaternions('quaternion_data.txt')

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.set_xlim(-1, 1)
ax.set_ylim(-1, 1)
ax.set_zlim(-1, 1)

# Initial vector [1, 0, 0] just for demonstration
line, = ax.plot([0, 1], [0, 0], [0, 0], 'r-')

ani = animation.FuncAnimation(fig, update_quaternion, frames=len(quaternions),
                              fargs=(quaternions, line), interval=100)

plt.show()
