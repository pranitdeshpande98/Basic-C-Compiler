#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A sample Linux kernel module");
MODULE_VERSION("0.1");

static int major_number = 0;

static ssize_t my_read(struct file *filep, char __user *buffer, size_t length, loff_t *offset)
{
    printk(KERN_INFO "my_read() called\n");
    return 0;
}

static ssize_t my_write(struct file *filep, const char __user *buffer, size_t length, loff_t *offset)
{
    printk(KERN_INFO "my_write() called\n");
    return length;
}

static int my_open(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "my_open() called\n");
    return 0;
}

static int my_release(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "my_release() called\n");
    return 0;
}

static struct file_operations fops = {
    .read = my_read,
    .write = my_write,
    .open = my_open,
    .release = my_release
};

static int __init my_init(void)
{
    printk(KERN_INFO "my_init() called\n");

    major_number = register_chrdev(0, "my_device", &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "Failed to register device: %d\n", major_number);
        return major_number;
    }

    printk(KERN_INFO "Registered device with major number %d\n", major_number);

    return 0;
}

static void __exit my_exit(void)
{
    printk(KERN_INFO "my_exit() called\n");

    unregister_chrdev(major_number, "my_device");
    printk(KERN_INFO "Unregistered device with major number %d\n", major_number);
}

module_init(my_init);
module_exit(my_exit);
