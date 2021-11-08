#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/time.h>
#include <linux/spinlock.h>
#define MODULE_NAME "TIMER_TEST"
#define SLEEP (1 * HZ)

struct info_tim {
	int val;
	struct timer_list timer;
 	spinlock_t lock;
 	bool isActive;
};

struct info_tim timer_test = {};

void timer_callback(struct timer_list *timer) {
	struct info_tim *data = from_timer(data, timer, timer);
	data->val++;
	printk(KERN_INFO "[%s] val is = %d\n", __func__, data->val);
	spin_lock(&data->lock);
	if (data->isActive)
		mod_timer(timer, jiffies + SLEEP);
	spin_unlock(&data->lock);
}

int __init timer_init(void) {

	printk("[%s] ################timer init################\n", __func__);

	/* initialization */
	timer_test.isActive = true;
	spin_lock_init(&timer_test.lock);
	timer_setup(&timer_test.timer, timer_callback, 0);

	/* 추가한 부분 : register timer */
	mod_timer(&timer_test.timer, jiffies + SLEEP);
	return 0;
}

/*
	빠져있는 함수 : register timer

	mod_timer(&timer_test.timer, jiffies + SLEEP);
*/

void __exit timer_exit(void) {
	int ret;
	spin_lock(&timer_test.lock);
	timer_test.isActive = false;
	ret = del_timer(&timer_test.timer);
	spin_unlock(&timer_test.lock);
	printk("[%s] ################timer exit################, ret = %d\n", __func__, ret);
}

module_init(timer_init);
module_exit(timer_exit);
MODULE_LICENSE("GPL");
