# KalmanFilter
Developing a Kalman filter algorithm to build my experience with them before working on avionics for spaceshot this spring.

As I go through the process of developing this algo, I am following [this](https://www.kalmanfilter.net/alphabeta.html) tutorial.

There are 5 main equations for the Kalman filter:

1. State Update Equation:

**For POSITION:**

$estimated = predicted * \alpha (measurement_{n} - predicted)$

**For VELOCITY:**

$estimated = predicted * \beta (\frac{measurement_{n} - predicted}{\Delta t})$


- $estimated$ represents the Kalman filter's guess on the state.
- $predicted$ is given by the state prediction made in the previous time step.
- $\alpha$ is the Kalman gain. If the measurement accuracy is high, alpha should approach 1, as this will make the measurement influence the equation more. If the measurement accuracy is low, alpha should approach 0 for the same reason.
- $measurement_n$ is the measurement taken by the sensor at time n. In my code, this is represented by a time series array.

2. State Extrapolation Equation:


