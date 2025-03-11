#include <linux/hid.h>
#include <linux/module.h>

#define USB_VENDOR_ID_TOPRE			0x0853
#define USB_DEVICE_ID_TOPRE_REALFORCE_R3S_87			0x0301

static __u8 *topre_report_fixup(struct hid_device *hdev, __u8 *rdesc,
				      unsigned int *rsize)
{
	if (*rsize >= 106 && rdesc[28] == 0x29 && rdesc[29] == 0xe7 &&
				    rdesc[30] == 0x81 && rdesc[31] == 0x00) {
		rdesc[31] = 0x02;
	}
	return rdesc;
}

static const struct hid_device_id topre_id_table[] = {
	{ HID_USB_DEVICE(USB_VENDOR_ID_TOPRE,
			 USB_DEVICE_ID_TOPRE_REALFORCE_R3S_87) },
	{ }
};

MODULE_DEVICE_TABLE(hid, topre_id_table);

static struct hid_driver topre_driver = {
	.name			= "topre",
	.id_table		= topre_id_table,
	.report_fixup		= topre_report_fixup,
};

module_hid_driver(topre_driver);
MODULE_LICENSE("GPL");
