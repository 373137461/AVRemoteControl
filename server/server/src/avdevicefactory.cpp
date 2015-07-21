#include "precompile.hpp"
#include "avdevicefactory.hpp"

AV_NAMESPACE_BEGIN

AVDeviceFactory::AVDeviceFactory()
{
}


AVDeviceFactory::~AVDeviceFactory()
{
}

int AVDeviceFactory::show_devices()
{
	AVInputFormat *ifmt  = NULL;
	AVOutputFormat *ofmt = NULL;
	const char *last_name;
	int is_dev;

	printf("%s\n"
			" D. = Demuxing supported\n"
			" .E = Muxing supported\n"
			" --\n", "Devices:");
	last_name = "000";
	for (;;) {
		int decode = 0;
		int encode = 0;
		const char *name      = NULL;
		const char *long_name = NULL;

		while ((ofmt = av_oformat_next(ofmt))) {
			if(is_device(ofmt->priv_class)){
				if ((!name || strcmp(ofmt->name, name) < 0) &&
						strcmp(ofmt->name, last_name) > 0) {
					name      = ofmt->name;
					long_name = ofmt->long_name;
					encode    = 1;
				}
			}
		}
		while ((ifmt = av_iformat_next(ifmt))) {
			if(is_device(ifmt->priv_class)){
				if ((!name || strcmp(ifmt->name, name) < 0) &&
						strcmp(ifmt->name, last_name) > 0) {
					name      = ifmt->name;
					long_name = ifmt->long_name;
					encode    = 0;
				}
				if (name && strcmp(ifmt->name, name) == 0)
					decode = 1;
			}
		}
		if (!name)
			break;
		last_name = name;

		printf(" %s%s %-15s %s\n",
				decode ? "D" : " ",
				encode ? "E" : " ",
				name,
				long_name ? long_name:" ");
	}
	return 0;
}

AV_NAMESPACE_END

#if 0
int main()
{
	av_register_all();
	avformat_network_init();
	avdevice_register_all();
	av::AVDeviceFactory factory;
	factory.show_devices();
	return 0;
}
#endif
