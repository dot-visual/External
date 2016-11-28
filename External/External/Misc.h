
class Misc
{
public:
	void BunnyHop();
	void SetBhop();
	bool GetBhop();

private:
	bool m_bhop;
};
extern Misc* g_pMisc;