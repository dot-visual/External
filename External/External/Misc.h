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

	//Aim-Bot Prototypes
	float CloseEnt();
	void Aimbot();
	void Reading(bool on);
	void readshit();
	void myCalcAngle(float *src, float *dst, float *angles, int fFlags);
	float closeEnt();
	float get3d(float X, float Y, float Z, float eX, float eY, float eZ);

private:
	bool m_bhop;
	bool m_trigger;
	bool m_glow;
};
extern Misc* g_pMisc;