#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>
 
static int foo;
static int baz;
static int bar;

static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
        dump_stack();
        int ret;
        ret=sprintf(buf, "%d", foo);
        printk("data string is %s\n", buf);
        return ret;
}

static ssize_t foo_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count) {
        dump_stack();
	    sscanf(buf, "%d", &foo);
	    printk("Data is %d\n", foo);
	    return count;
}

static ssize_t baz_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
    	int var;
        dump_stack();
    	var = baz;
        printk("Data var (from baz) is %d\n", var);	    
   	    return sprintf(buf, "%d\n", var);
}

static ssize_t baz_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count) {
        int var;
        dump_stack();
		sscanf(buf, "%d", &var);
        baz = var;
        printk("Data baz is %d\n", baz);
        return count;
}

static ssize_t bar_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
    	int var;
        dump_stack();
    	var = bar;
        printk("Data var (from bar) is %d\n", var);
        return sprintf(buf, "%d\n", var);
}

static ssize_t bar_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count) {
        int var;
        dump_stack();
        sscanf(buf, "%d", &var);
        bar = var;
        printk("Data bar is %d\n", bar);
    	return count;
}

static struct kobj_attribute foo_attribute =
            	__ATTR(foo, 0664, foo_show, foo_store);
static struct kobj_attribute baz_attribute =
            	__ATTR(baz, 0664, baz_show, baz_store);
static struct kobj_attribute bar_attribute =
            	__ATTR(bar, 0664, bar_show, bar_store);


static struct attribute *attrs[] = {
	&foo_attribute.attr,
	&baz_attribute.attr,
	&bar_attribute.attr,
	NULL,	
};

static struct attribute_group attr_group = {
	.attrs = attrs,
};

static struct kobject *example_kobj;

static int __init example_init(void) {
	int retval=0;
	example_kobj = kobject_create_and_add("kobject_example", kernel_kobj);
	if (!example_kobj)
		return -ENOMEM; 
	retval = sysfs_create_group(example_kobj, &attr_group);
	return retval;
}

static void __exit example_exit(void) {
	kobject_put(example_kobj);
}

module_init(example_init);
module_exit(example_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Greg Kroah-Hartman <greg@kroah.com>");
