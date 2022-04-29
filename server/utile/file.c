char *load_file(char *path)
{
	FILE *f = fopen(path, "rb");
    if (f == NULL)
		return NULL;
    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *ret = malloc(size);
    fread(ret, size, 1, f);
    fclose(f);
    ret[size] = 0;
	return ret;
}
