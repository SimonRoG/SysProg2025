# ЛАБОРАТОРНА РОБОТА 3

## Створення віртуального символьного пристрою у варіанті модуля ядра Linux і прототипів системних викликів

**Виконав:** Семен Прохода ІП-з31

### Завдання до роботи

**Варіант 5:**

Створити модуль ядра Linux, який обчислює факторіал переданого числа з символьного пристрою.

### Лістинг програми

[**_GitHub_**](https://github.com/SimonRoG/SysProg2025/blob/main/3/readme.md)

#### Код модуля ядра: [`factorial.c`](factorial.c)

```c
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#define DEVICE_NAME "factorial"
#define BUF_LEN 32

MODULE_DESCRIPTION("Character device calculates factorial");
MODULE_AUTHOR("Semen Prokhoda");
MODULE_LICENSE("GPL");

static int major;

static unsigned long long factorial(int n) {
	unsigned long long res = 1;
	for (int i = 1; i <= n; i++)
		res *= i;
	return res;
}

static ssize_t device_write(struct file* file, const char __user* user_buffer, size_t size, loff_t* offset) {
	ssize_t len = min(BUF_LEN - 1, size);
	if (len <= 0)
		return 0;

	int num;
	char buf[BUF_LEN];
	unsigned long long fact;

	if (copy_from_user(buf, user_buffer, len))
		return -EFAULT;

	buf[len] = 0;

	sscanf(buf, "%d", &num);
	if (num > 20) {
		printk(KERN_WARNING "factorial: %d is too big\n", num);
		return -EINVAL;
	}
	if (num < 0) {
		printk(KERN_WARNING "factorial: %d is negative\n", num);
		return -EINVAL;
	}

	fact = factorial(num);
	printk(KERN_INFO "factorial: %d! = %llu\n", num, fact);

	*offset += len;
	return len;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .write = device_write,
};

static int factorial_init(void) {
	major = register_chrdev(0, DEVICE_NAME, &fops);
	printk(KERN_INFO "factorial: registered. %d\n", major);
	return 0;
}

static void factorial_exit(void) {
	unregister_chrdev(major, DEVICE_NAME);
	printk(KERN_INFO "factorial: unregistered.\n");
}

module_init(factorial_init);
module_exit(factorial_exit);
```

#### Makefile для збірки модуля ядра: [`Makefile`](Makefile)

```make
obj-m += factorial.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

install:
	insmod factorial.ko

uninstall:
	rmmod factorial.ko
```

### Тестування

-   `make` - для побудови модуля ядра
-   `make install` - для встановлення модуля
-   `mknod /dev/factorial c $(grep factorial /proc/devices | awk '{print $1}') 0` - для створення символьного пристрою
-   `chmod 666 /dev/factorial` - для надання прав доступу до пристрою
-   `echo 6 > /dev/factorial` - для запису числа
-   `make uninstall` - для видалення модуля
-   `dmesg | tail` - для перегляду результатів
-   `make clean` - для очищення збірки
-   `rm -f /dev/factorial` - для видалення символьного пристрою

### Результати

1.  Збірка модуля

```bash
$ make
make -C /lib/modules/6.17.9-arch1-1/build M=/home/semen/Nextcloud/Documents/LABS/SysProg/3 modules
make[1]: Entering directory '/usr/lib/modules/6.17.9-arch1-1/build'
make[2]: Entering directory '/home/semen/Nextcloud/Documents/LABS/SysProg/3'
  CC [M]  factorial.o
  MODPOST Module.symvers
  CC [M]  factorial.mod.o
  CC [M]  .module-common.o
  LD [M]  factorial.ko
  BTF [M] factorial.ko
make[2]: Leaving directory '/home/semen/Nextcloud/Documents/LABS/SysProg/3'
make[1]: Leaving directory '/usr/lib/modules/6.17.9-arch1-1/build'
```

2.  Встановлення модуля

```bash
$ sudo make install
insmod factorial.ko
```

3.  Створення символьного пристрою та запис числа

```bash
$ sudo mknod /dev/factorial c $(grep factorial /proc/devices | awk '{print $1}') 0
$ sudo chmod 666 /dev/factorial
$ echo 6 > /dev/factorial
```

4.  Видалення модуля

```bash
$ sudo make uninstall
rmmod factorial.ko
```

5.  Перегляд результатів (останні 5 записів)

```bash
$ sudo dmesg | tail -5
[16263.593207] factorial: registered. 508
[16285.964170] factorial: 21 is too big
[16301.987621] factorial: -1 is negative
[16336.779916] factorial: 6! = 720
[16347.589040] factorial: unregistered.
```

6.  Очищення збірки

```bash
$ make clean
make -C /lib/modules/6.17.9-arch1-1/build M=/home/semen/Nextcloud/Documents/LABS/SysProg/3 clean
make[1]: Entering directory '/usr/lib/modules/6.17.9-arch1-1/build'
make[2]: Entering directory '/home/semen/Nextcloud/Documents/LABS/SysProg/3'
  CLEAN   Module.symvers
make[2]: Leaving directory '/home/semen/Nextcloud/Documents/LABS/SysProg/3'
make[1]: Leaving directory '/usr/lib/modules/6.17.9-arch1-1/build'
```

### Висновок

У ході виконання лабораторної роботи було створено модуля ядра Linux, який обчислює факторіал переданого числа з символьного пристрою. Реалізовано обробку помилок для некоректних та надто великих значень. Модуль успішно компілюється, встановлюється, тестується та видаляється. Результати роботи пристрою коректно відображаються у системному журналі.