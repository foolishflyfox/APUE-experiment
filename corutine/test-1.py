# test-1.py
# 定义生成器
def consume():
    print("enter consume")
    while True:
        # consumer 协程等待接收数据
        number = yield
        print("consumer: Get", number)
# 创建协程对象
consumer = consume()
print("created consumer")
# 启动协程
next(consumer)
print("after next")
for num in range(3):
    print("Create", num)
    consumer.send(num)
