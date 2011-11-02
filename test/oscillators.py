from scipy.signal import *
import matplotlib
import pylab

f0 = 441.		# fundamental frequency
fs = 44100.		# sample rate
si = f0/fs		# phase increment
P = int(fs/f0)		# period
t = arange(0,4+si,si)	# time vector

# plot

fig = pylab.figure()
fig.canvas.set_window_title('Elementary Phaseshapers')
ticks = matplotlib.ticker.FixedLocator([0,0.5,1])

def preplot(id):
	id += 610
	p = pylab.subplot(id)
	p.grid(True)
	p.yaxis.set_major_locator(ticks)
	return p

def postplot(p, showticklabels=False):
	if not showticklabels:
		p.xaxis.set_ticklabels('')
	else:
		pylab.xlabel('Time (samples, f0=441 Hz, fs=44.1 kHz)')
	pylab.ylim(-1.1, 1.1)
	pylab.xlim(0,301)
	pylab.ylabel('Level')

def saw_wave(x):
    pow2 = x * x
    rv = zeros(len(x))
    for n in range(0,len(x)):
        rv[n] = pow2[n] - pow2[n-1]
    rv = rv * fs/(4*f0)
    return rv

def tri_wave(x):
    par = x - (x*abs(x))
    rv = zeros(len(x))
    for n in range(0,len(x)):
        rv[n] = par[n] - par[n-1]
    rv = rv * fs/(2*f0)
    return rv

phi = t % 1	
steps = 2 * phi - 1
saw = saw_wave(steps)
tri = tri_wave(steps)

# -- unipolar modulo counter
#p1 = preplot(1)
#p1.plot(phi, "k", lw=2)
#postplot(p1)

# -- steps
p1 = preplot(1)
p1.plot(steps, "k", lw=2)
postplot(p1)

# -- saw
p2 = preplot(2)
p2.plot(saw, "k", lw=2)
postplot(p2)

# -- triangle
p3 = preplot(3)
p3.plot(tri, "k", lw=2)
postplot(p3)

# TODO square

pylab.show()

