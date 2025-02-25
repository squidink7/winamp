		/*
        * mod2wave.h
        * ----------
        * Purpose: Module to WAV conversion (dialog + conversion code).
        * Notes  : (currently none)
        * Authors: OpenMPT Devs
        * The OpenMPT source code is released under the BSD license. Read LICENSE for more details.
        */
		
		
		#pragma once
		
		#include "openmpt/all/BuildSettings.hpp"
		
		#include "StreamEncoder.h"
		#include "StreamEncoderSettings.h"
		#include "Settings.h"
		#include "ProgressDialog.h"
		
		
		OPENMPT_NAMESPACE_BEGIN
		
		
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// Direct To Disk Recording
		
		
		
		struct CWaveConvertSettings
		{
	std::vector<EncoderFactoryBase*> EncoderFactories;
	std::vector<std::unique_ptr<EncoderSettingsConf>> EncoderSettings;
		
	Setting<mpt::ustring> EncoderName;
	std::size_t EncoderIndex;
		
	StoredTags storedTags;
	FileTags Tags;
		
	int repeatCount;
	ORDERINDEX minOrder, maxOrder;
	SAMPLEINDEX sampleSlot;
	SEQUENCEINDEX minSequence, maxSequence;
		
	bool normalize : 1;
	bool silencePlugBuffers : 1;
	bool outputToSample : 1;
		
	std::size_t FindEncoder(const mpt::ustring &name) const;
	void SelectEncoder(std::size_t index);
	EncoderFactoryBase *GetEncoderFactory() const;
	const Encoder::Traits *GetTraits() const;
	EncoderSettingsConf &GetEncoderSettings() const;
	Encoder::Settings GetEncoderSettingsWithDetails() const;
	CWaveConvertSettings(SettingsContainer &conf, const std::vector<EncoderFactoryBase*> &encFactories);
		};
		
		
		class CWaveConvert: public CDialog
		{
		public:
	CWaveConvertSettings m_Settings;
	const Encoder::Traits *encTraits;
	CSoundFile &m_SndFile;
	uint64 m_dwSongLimit;
	ORDERINDEX m_nNumOrders;
		
	CComboBox m_CbnFileType, m_CbnSampleRate, m_CbnChannels, m_CbnDither, m_CbnSampleFormat, m_CbnSampleSlot;
	CSpinButtonCtrl m_SpinLoopCount, m_SpinMinOrder, m_SpinMaxOrder, m_SpinMinSequence, m_SpinMaxSequence;
		
	bool m_bGivePlugsIdleTime;
	bool m_bChannelMode;		// Render by channel
	bool m_bInstrumentMode;		// Render by instrument
		
	CEdit m_EditTitle, m_EditAuthor, m_EditURL, m_EditAlbum, m_EditYear;
	CComboBox m_CbnGenre;
	CEdit m_EditGenre;
		
		private:
	void FillFileTypes();
	void FillSamplerates();
	void FillChannels();
	void FillFormats();
	void FillDither();
	void FillTags();
		
	void LoadTags();
		
	void SaveEncoderSettings();
	void SaveTags();
		
		public:
	CWaveConvert(CWnd *parent, ORDERINDEX minOrder, ORDERINDEX maxOrder, ORDERINDEX numOrders, CSoundFile &sndFile, const std::vector<EncoderFactoryBase*> &encFactories);
		
		public:
	void UpdateDialog();
	BOOL OnInitDialog() override;
	void DoDataExchange(CDataExchange *pDX) override;
	void OnOK() override;
	afx_msg void OnCheckTimeLimit();
	afx_msg void OnCheckChannelMode();
	afx_msg void OnCheckInstrMode();
	afx_msg void OnFileTypeChanged();
	afx_msg void OnSamplerateChanged();
	afx_msg void OnChannelsChanged();
	afx_msg void OnDitherChanged();
	afx_msg void OnFormatChanged();
	afx_msg void OnPlayerOptions();
	afx_msg void OnExportModeChanged();
	afx_msg void OnSampleSlotChanged();
	DECLARE_MESSAGE_MAP()
		};
		
		
		class CDoWaveConvert: public CProgressDialog
		{
		public:
	const CWaveConvertSettings &m_Settings;
	CSoundFile &m_SndFile;
	mpt::ofstream &fileStream;
	const CString &caption;
	uint64 m_dwSongLimit;
	bool m_bGivePlugsIdleTime;
		
		public:
	CDoWaveConvert(CSoundFile &sndFile, mpt::ofstream &f, const CString &caption, const CWaveConvertSettings &settings, CWnd *parent = NULL)
: CProgressDialog(parent)
, m_Settings(settings)
, m_SndFile(sndFile)
, fileStream(f)
, caption(caption)
, m_dwSongLimit(0)
	{ }
	void Run() override;
		};
		
		
		OPENMPT_NAMESPACE_END
		