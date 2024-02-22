# KalmanFilter
Developing a Kalman filter algorithm to build my experience with them before working on avionics for spaceshot this spring.

As I go through the process of developing this algo, I am following [this](https://www.kalmanfilter.net/alphabeta.html) tutorial.

## Table of Contents:

1. [$\alpha$ - $\beta$ - $\gamma$ filter](#section1)
2. [Univariate Kalman Filter](#section2)
3. [Multivariate Kalman Filter](#section3)

## $\alpha$ - $\beta$ - $\gamma$ Filter: <a name='section1'></a>

This type of filter is used in the tutorial as a lead-up to the Kalman filter. While the Kalman filter treats each variable as random and uses standard distributions to create an estimate, the $\alpha$ - $\beta$ - $\gamma$ filter uses known system state equations (in this case, simple kinematic equations).

The filter makes use of two important equations for each variable (position, velocity, and acceleration): 

### 1. State Update Equation:

The point of these equations are to update our estimate of the true quantity considering a new measurement and that time has passed. The coefficients can be changed based on sensor accuracy.

**For POSITION:**

$position_{est} = position_{pred} * \alpha (measurement_{n} - position_{pred})$

**For VELOCITY:**

$velocity_{est} = velocity_{pred} * \beta (\frac{measurement_{n} - position_{pred}}{\Delta t})$

**For ACCELERATION:**

$acceleration_{est} = acceleration_{pred} * \gamma (\frac{measurement_n - position_{pred}}{0.5 (\Delta t)^2})$


- $example_{est}$ represents the Kalman filter's guess on the state.
- $example_{pred}$ is given by the state prediction made in the previous time step.
- $\alpha$, $\beta$, and $\gamma$ are the gains. If the measurement accuracy is high, alpha/beta should approach 1, as this will make the measurement influence the equation more. If the measurement accuracy is low, alpha/beta should approach 0 for the same reason.
- $measurement_n$ is the position measurement taken by the sensor at time n. In my code, this is represented by a time series array.

### 2. State Extrapolation Equation:

This equation is given by the system-- in this case, we are using 1d kinematics. This gives us the equation:

$x_f = x_i + (v  \Delta t) + 0.5 a (\Delta t)^2$

$v_f = v_i + a \Delta t$

$a_f = a_i$ (assuming constant acceleration)

where $\Delta t$ is the sampling period.


This filter is very useful if the system is relatively simple, and the equations governing the system dynamics are known. However, most real life systems have more unpredictability and extremely complicated equations, which is why the Kalman filter is widely used.

## The Uni-Variate Kalman Filter <a name='section2'></a>

This filter uses the state update equations but also accounts for the variance in the various measurements. This allows the algorithm to converge close to the true value.

It does this by not only predicting the various system states (position, velocity, acceleration etc.), but also the *VARIANCE* of those system states. In other words, it uses the measured states and respective variances, as well as the *estimated* states and variances.

### Version 1: Constant Dynamics With No Process Noise

There are two types of noise that can affect measurements that the Kalman filter can account for. 
- **Measurement Noise:** This is noise caused by the error in the measurement due to sensor inaccuracy.
- **Process Noise:** This is noise caused by external impacts that change the physical state of the system. For example, if we are measuring the position of a plane, wind might create process noise.

We still follow the general algorithm:

0. Initialize
1. Measure
2. Update
3. Predict

and then loop over 1, 2, and 3 for all the data points in the set.

We get the following 5 equations:

#### State Update Equations:
1. **State Equation:** 

$x_{est} = x_{pred} + K_n (z_n - x_{pred})$ 

(where $z_n$ is the measurement at that time and $K_n$ is the Kalman Gain)

2. **Covariance Update Equation:**

$var = (1 - K_n) var_{pred}$

3. **Kalman Gain Equation:**

$K_n = \frac{var_{pred}}{var_{pred} + r_n}$ 

(where $r_n$ is the sensor variance)

#### State Prediction Equations:

4. **State Extrapolation Equation:** This equation updates the estimate for the variable according to the system dynamics. In the examples here this is either constant or in accordance with simple kinematics.

5. **Covariance Extrapolation Equation:** This equation does the same thing as the State Extrapolation Equation, but instead of updating the estimate for the state, it updates the estimate for the *covariance* of the estimated state. With process noise added, whatever covariance is of the highest degree/constant should be += with process noise covariance.

### Process Noise Details:

If we use the constant dynamic system to measure something with a constant increase, for example the temperature of a pot of water heating up linearly using a small process noise covariance, we will get a lag error.
- This means that while the Kalman Filter will eventually converge on the correct slope, the actual values will lag behind the true values by a potentially significant amount.

We can fix this, even if our system dynamics are not well defined. **Increasing the process noise variance** is the key.
- Once we do this, the Kalman filter is able to accurately follow and estimate the true temperature of the water. YAY!

## Multi-Variate Kalman Filter <a name='section3'></a>

Many systems take place in more than one dimension. In order to deal with this, we can use matrix formulas and linear algebra. As a result, this gets kind of mathy.

### Space State Extrapolation Equation:

We can represent the space state with two equations:

1. $\mathbf{\dot x(t)} = \mathbf{Ax(t)} + \mathbf{Bu(t)}$

2. $\mathbf{y(t)} = \mathbf{Cx(t)} + \mathbf{Du(t)}$

in which $\mathbf{\dot x(t)} = $ the derivative of the state vector, and $\mathbf{y(t)} = $ the output vector, and $\mathbf{x(t)}$ is the measured state vector and $\mathbf{u(t)}$ is a control input vector.

In higher order systems, we can solve for $\mathbf{A}$, $\mathbf{B}$, $\mathbf{C}$, and $\mathbf{D}$  using principles from differential equations. We do all of this to be able to create the **State Extrapolation Equation** for the system. This equation takes the form of 

3. $\mathbf{\hat x_{n+1, n}} = \mathbf{F \hat x_{n,n}} + \mathbf{G \hat u_{n,n}} + \mathbf{w_n}$

in which the hat represents estimation, $\mathbf{\hat u_{n,n}}$ represents a control input, and $\mathbf{w_n}$ represents the process noise vector.

In order to find $\mathbf{F}$, we need to solve the differential equation (1.) in order to get $x_{n+1}$ in terms of $x_n$ and $\mathbf{A}$. Using separation of variables, we get the following solution:

4. $x_{n+1} = x_n e^{\mathbf{A} \Delta t}$

If we extend this to the whole state vector, it makes sense that

5. $\mathbf{F} = e^{\mathbf{A} \Delta t}$

Taking the exponential of a matrix can be done with a Taylor Polynomial. If we replace $\mathscr{x}$ with the matrix $\mathbf{X}$ in the series expansion, we get:

6. $e^{\mathbf{X}} = \sum_{k=0}^{\infty} \frac{1}{k!} \mathbf{X}^k$

which is kind of neat. In most cases, $\mathbf{X}^k$ will quickly converge to 0, so we only have to worry about the first few terms, which is nice. In addition, it is important to note that $\mathbf{X}^0 = \mathbf{I}$.

For zero-order hold sampling (which is what we have in a real life rocket scenario-- sensors sample at 10 Hz on our avionics board I believe), we have a consistent $\Delta t$. In other words, in this case

7. $x_{n+1, n} = x(t + \Delta t)$

which means that

8. $\mathbf{x(t + \Delta t)} = e^{\mathbf{A} \Delta t} \mathbf{x(t)} + \int_{0}^{\Delta t} e^{\mathbf{A}t} dt \mathbf{B} \mathbf{u(t)}$

We notice that this equation looks similar in form to (3.), giving us

9. $\mathbf{F} = e^{\mathbf{A} \Delta t}$

and 

10. $\mathbf{G} = \int_{0}^{\Delta t} e^{\mathbf{A}t} dt \mathbf{B}$

As a result, once we solve for $\mathbf{A}$ and $\mathbf{B}$, we can simply plug this into (9.) and (10.) to solve for $\mathbf{F}$ and $\mathbf{G}$.

### Covariance Extrapolation Equation:

The general form of this equation is:

1. $\mathbf{P_{n+1,n}} = \mathbf{FP_{n,n}} \mathbf{F}^T + \mathbf{Q}$

where ${\mathbf{{P}_{n,n}}}$ is the covariance matrix of the state estimate, ${\mathbf{{P}_{n+1,n}}}$ is the covariance matrix of the state prediction, $\mathbf{F}$ is the state transition matrix derived in the *State Extrapolation Equation* and $\mathbf{Q}$ is the process noise matrix.

### "Auxiliary Equations: Measurement vector + Uncertainties

#### Measurement Vector:

Generalize measurement equation:

$\mathbf{z_n} = \mathbf{Hx_n} + \mathbf{v_n}$

where $\mathbf{z_n}$ is the measurement vector, $\mathbf{x_n}$ is the true (hidden) system state, $\mathbf{H}$ is the observation matrix (basically what process is there between observed state and true state), and $\mathbf{v_n}$ is a random noise vector.

#### Covariance Equations

Sources: 
[michaelscheinfeild](https://medium.com/@michaelscheinfeild/alpha-beta-gamma-and-kalman-filter-bfd21041d940),
[Kalman Filter from the Ground Up: Alex Becker](https://www.kalmanfilter.net/kalman1d.html), 