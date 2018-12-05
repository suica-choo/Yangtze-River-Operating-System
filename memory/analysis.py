file = open("memory_access_result.txt", "r")
data = []
count = 0
length = 0
for line in file:
	count += 1
	loop = line.split(" ")
	length = len(loop)
	data.append(loop)


res = []
for k in range(18):
	res.append(0)

for i in range(count):
	for j in range(length-1):
		res[j] += float(data[i][j])

for k in range(length-1):
	res[k] = res[k]/count
	num = 0.37*res[k]
	print("loop: %s time: %s" % (res[k], num))

file.close()
