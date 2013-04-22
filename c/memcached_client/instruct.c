// Add a few servers
mc_server_add(mc, "127.0.0.1", "11211");
mc_server_add(mc, "127.0.0.1", "11212");
mc_server_add(mc, "127.0.0.1", "11213");

// Add a key
mc_add(mc, key, keylen, flags, expire, bytes, val);

// Get a key, caller has to free(3) memory
void *blah = mc_aget(mc, key, keylen);
free(blah);

// Perform a multi-key request
struct memcache_req *req = mc_req_new();
mc_req_add(req, key1, key1_len);
mc_req_add(req, key2, key2_len);
mc_get(mc, req);
// Process the results (need a better interface to looping through 
results)

// Perform a multi-key request the easy way (this is my preferred way 
of getting data):
req = mc_req_new();
res1 = mc_req_add(req, key1, key1_len);
res2 = mc_req_add(req, key2, key2_len);
mc_get(mc, req);
// Play with res1/res2 w/o any looping through req


// Complex multi-key get example:
// Grab the response object that will be used to store a given key
struct memcache_res *res = mc_req_add(req, key3, key3_len);
res->size = 1024;				// Allocate our own memory a head of time (useful 
for loops)
res->val = malloc(res->size);
res->free_on_delete = 't';

// Perform the get
mc_get(mc, req);
mc_res_free(req, res);

// Get stats from the whole cluster
struct memcache_server_stats *s = mc_stats(mc);
mc_server_stats_free(s);

// Storage commands:
mc_add(mc, key, key_len, flags, expire, bytes, val);
mc_replace(mc, key, key_len, flags, expire, bytes, val);
mc_set(mc, key, key_len, flags, expire, bytes, val);

// Delete commands:
mc_delete(mc, key, key_len, hold_timer);

// Atomic opts:
mc_incr(mc, key, key_len, 1);
mc_decr(mc, key, key_len, 1);

mc_free(mc);
