import matplotlib.pyplot as plt
import subprocess

file = "C:\\secondSemLab\\Labwork9\\cmake-build-release\\bin\\lab9.exe"
max_elements = 50000
per_each = 1000
mas = [file, str(max_elements), str(per_each)]

output = list(map(int, subprocess.run(mas, stdout=subprocess.PIPE).stdout.decode("utf-8").split()))
print(output)

x1 = []
y1 = []
x2 = []
y2 = []


for i in range(0, len(output), 2):
    y1.append(output[i])

for i in range(1, len(output), 2):
    y2.append(output[i])

k = max_elements / per_each
for i in range(per_each, max_elements + 1, per_each):
    x1.append(i)
    x2.append(i)


plt.plot(x1, y1, color='r', label='STD')
plt.plot(x2, y2, color='b', label='Pool')

plt.xlabel("Number of added elements")
plt.ylabel("Time in microseconds")
plt.title("STD and Pool Allocators Comparison")

plt.legend()
plt.show()
