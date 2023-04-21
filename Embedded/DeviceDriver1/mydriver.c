#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define NOD_MAJOR 100
#define NOD_NAME "mydriver"

MODULE_LICENSE("GPL");

struct Node{
	int age;
	char name[100];
};

static int mydriver_open(struct inode *inode, struct file *filp) {
	printk( KERN_INFO "welcome\n");
	return 0;
}

static int mydriver_release(struct inode *inode, struct file *filp) {
	printk( KERN_INFO "release\n");
	return 0;
}

static ssize_t mydriver_read(struct file *filp, char *buf, size_t count, loff_t *ppos) {
	buf[0] = 'h';
	buf[1] = 'i';
	buf[2] = '\0';
	return count;
}

static ssize_t mydriver_write(struct file *filp, const char *buf, size_t count, loff_t *ppos) {
	printk( KERN_INFO "app msg : %s\n", buf);
	return count;
}

static long mydriver_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
	struct Node user;
	struct Node* userp = &user;
	int ret;
	void *p = (void *)(arg);
	switch(cmd) {
		case _IO(0, 3):
			printk( KERN_ALERT "ssafy studying!!!\n");
			break;
		case _IO(0, 4):
			ret = copy_from_user((void *)userp, p, sizeof(struct Node));
			userp->age++;
			ret = copy_to_user((void *)arg, (void*)userp, sizeof(struct Node));
			printk( KERN_ALERT "THIS IS SPARTA!!!\n");
			printk( KERN_INFO "%sis grow up!, %d!!\n", userp->name, userp->age);
			break;
		default:
			return -EINVAL;
	}
	return 0;
}

static struct file_operations fops = {
	.open = mydriver_open,
	.release = mydriver_release,
	.read = mydriver_read,
	.write = mydriver_write,
	.unlocked_ioctl = mydriver_ioctl,
};

static int mydriver_init(void) {
	if( register_chrdev(NOD_MAJOR, NOD_NAME, &fops) < 0) {
		printk("INIT FAIL\n");
	}
	printk( KERN_INFO "hi\n");
	return 0;
}

static void mydriver_exit(void) {
	unregister_chrdev(NOD_MAJOR, NOD_NAME);
	printk( KERN_INFO "bye\n");
}

module_init(mydriver_init);
module_exit(mydriver_exit);
