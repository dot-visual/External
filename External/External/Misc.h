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

	void RCS();
	void SetRCS();
	bool GetRCS();

	void Aimbot();
	void SetAimbot();
	bool GetAimbot();

	void smoothAngle(float *src, float *dest);

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

	void Reading(bool on);
	void readshit();
	void myCalcAngle(float *src, float *dst, float *angles, int fFlags);
	float closeEnt();
	float get3d(float X, float Y, float Z, float eX, float eY, float eZ);
	void clampAngl(float *ang);

private:
	bool m_bhop;
	bool m_trigger;
	bool m_glow;
	bool m_rcs;
	bool m_aimbot;

	float oldAngle[3];
};
extern Misc* g_pMisc;