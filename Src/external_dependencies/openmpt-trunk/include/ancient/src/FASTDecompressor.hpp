	/* Copyright (C) Teemu Suutari */
	
	#ifndef FASTDECOMPRESSOR_HPP
	#define FASTDECOMPRESSOR_HPP
	
	#include "XPKDecompressor.hpp"
	
	namespace ancient::internal
	{
	
	class FASTDecompressor : public XPKDecompressor
	{
	public:
FASTDecompressor(uint32_t hdr,uint32_t recursionLevel,const Buffer &packedData,std::shared_ptr<XPKDecompressor::State> &state,bool verify);
	
virtual ~FASTDecompressor();
	
virtual const std::string &getSubName() const noexcept override final;
	
virtual void decompressImpl(Buffer &rawData,const Buffer &previousData,bool verify) override final;
	
static bool detectHeaderXPK(uint32_t hdr) noexcept;
static std::shared_ptr<XPKDecompressor> create(uint32_t hdr,uint32_t recursionLevel,const Buffer &packedData,std::shared_ptr<XPKDecompressor::State> &state,bool verify);
	
	private:
const Buffer	&_packedData;
	};
	
	}
	
	#endif
	