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