#include <linux/module.h>   
#include <linux/kernel.h>   
#include <linux/init.h> 
#include <linux/types.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>


#define START_IP_ADDRESS htonl(0x5250adaa) // Example: 82.80.0.0
#define END_IP_ADDRESS   htonl(0x5250ffff) // Example: 82.80.255.255


// Netfilter hook function to monitor incoming packets
static unsigned int netfilter_hook_func(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
    struct iphdr *ip_header;
    
    static int firstIn = 1;
    ip_header = ip_hdr(skb);
        
    if(firstIn){
    	printk(KERN_INFO "ip_str_header: %pI4\n", &ip_header->saddr);
        printk(KERN_INFO "Pre Hook Register\n");
        firstIn = 0;
    }


    if (!skb) {
        printk(KERN_INFO "Packet not correct\n");
        return NF_DROP;
    }

	
	
    if (ip_header != NULL) {
        __be32 src_addr = ip_header->saddr; // No need to use ntohl if we're just comparing

        if (src_addr >= START_IP_ADDRESS && src_addr < END_IP_ADDRESS) {
            // Do something with packets from this address range
            printk(KERN_INFO "Packet from Source IP: %pI4 droped\n", &ip_header->saddr);
            return NF_DROP;
        }
        
        printk(KERN_INFO "Packet from Source IP: %pI4 accepted\n", &ip_header->saddr);
        return NF_ACCEPT;
    }
    
    // Log source and destination IP addresses
    printk(KERN_INFO "Source IP: %pI4, Destination IP: %pI4\n",
           &ip_header->saddr, &ip_header->daddr);

    return NF_ACCEPT;
}


// Netfilter hook struct
static struct nf_hook_ops my_nf_hook = {
    .hook = netfilter_hook_func,
    .hooknum = NF_INET_PRE_ROUTING, // Intercept packets at the pre-routing stage
    .pf = PF_INET, // IPv4 packets
    .priority = NF_IP_PRI_FIRST,
};


// Module initialization
static int __init netfilter_monitor_init(void) {
    // Register the netfilter hook
    if (nf_register_net_hook(&init_net, &my_nf_hook) != 0) {
        printk(KERN_ERR "Failed to register netfilter hook\n");
        return -EFAULT;
    }

    printk(KERN_INFO "Netfilter module loaded\n");
    return 0;
}

// Module cleanup
static void __exit netfilter_monitor_exit(void) {
    // Unregister the netfilter hook
    nf_unregister_net_hook(&init_net, &my_nf_hook);
    
    printk(KERN_INFO "Pre Hook un Register\n");
}

module_init(netfilter_monitor_init);
module_exit(netfilter_monitor_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Roee Benezra");
MODULE_DESCRIPTION("Netfilter Packet Monitoring Module");


