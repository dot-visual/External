class Misc
{
public:
	Misc();
	~Misc();
	void BunnyHop();
	void SetBhop();
	bool GetBhop();

	void Triggerbot();
	void SetTrigger();
	bool GetTrigger();

	void Glow();
	void SetGlow();
	bool GetGlow();

	void AutoPistol();
	void NoFlash();
	float GlowTerroristRed;
	float GlowTerroristGreen;
	float GlowTerroristBlue;
	float GlowTerroristAlpha;
	bool m_bRenderWhenOccluded;
	bool m_bRenderWhenUnoccluded;


private:
	bool m_bhop;
	bool m_trigger;
	bool m_glow;
};
extern Misc* g_pMisc;